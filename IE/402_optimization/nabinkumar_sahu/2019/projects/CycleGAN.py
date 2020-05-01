#!/usr/bin/env python
# coding: utf-8

import os
from os import listdir, makedirs, getcwd, remove
from os.path import isfile, join, abspath, exists, isdir, expanduser
import numpy as np
import math
import torchvision.transforms as transforms
from torchvision.utils import save_image
from torch.utils.data import Dataset, DataLoader
from torchvision import datasets
from torch.autograd import Variable
import torch.nn as nn
import torch.nn.functional as f
import torch
from torch import Tensor
import matplotlib.pyplot as plt
import scipy
import h5py
from scipy import io as sio
from scipy.io import savemat
from scipy.io import loadmat
#import visdom
import itertools
#import time
#import utils

#viz = visdom.Visdom()
batch_size = 1000
num_epochs = 150
#decay_epoch = 75
learning_rate = 0.0002
lambda_cyc = 10
lambda_id = 5

cuda = True if torch.cuda.is_available() else False
print("****************Cuda status: ", cuda,"******************")


#Dataloader
class speech_data(Dataset):
    
    def __init__(self, folder_path):
        self.path = folder_path
        self.files = listdir(folder_path)
        self.length = len(self.files)
        
    def __getitem__(self, index):
        d = loadmat(join(self.path, self.files[int(index)]))
        n = int(index)
        while(n==index):
            n = np.random.randint(0,n)
        d1 = loadmat(join(self.folder_path, "target", self.files[n]))
        return np.array(d['Feat']), np.array(d1['Clean_cent']) #nam, whisper
    
    def __len__(self):
        return self.length


#Generator
class Generator(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(Generator, self).__init__()
        
        self.fc1 = nn.Linear(input_dim, 512)
        self.relu1 = nn.ReLU()
        
        self.fc2 = nn.Linear(512, 512)
        self.relu2 = nn.ReLU()
        
        self.fc3 = nn.Linear(512, 512)
        self.relu3 = nn.ReLU()
        
        self.out_layer = nn.Linear(512, output_dim)
    
    def forward(self, z):
        out = self.fc1(z.type(torch.cuda.FloatTensor)) if cuda else self.fc1(z.type(torch.FloatTensor))
        out = self.relu1(out)
        out = self.fc2(out)
        out = self.relu2(out)
        out = self.fc3(out)
        out = self.relu3(out)
        out = self.out_layer(out)
        return out


#Discriminator
class Discriminator(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(Discriminator, self).__init__()
        
        self.fc1 = nn.Linear(input_dim, 512)
        self.tanh1 = nn.Tanh()
        
        self.fc2 = nn.Linear(512, 512)
        self.tanh2 = nn.Tanh()
        
        self.fc3 = nn.Linear(512, 512)
        self.tanh3 = nn.Tanh()
        
        self.out_layer = nn.Linear(512, output_dim) #-------------
        self.out_sigmoid = nn.Sigmoid()
    
    def forward(self, z):
        out = self.fc1(z.type(torch.cuda.FloatTensor)) if cuda else self.fc1(z.type(torch.FloatTensor))
        out = self.tanh1(out)
        out = self.fc2(out)
        out = self.tanh2(out)
        out = self.fc3(out)
        out = self.tanh3(out)
        out = self.out_layer(out)
        out = self.out_sigmoid(out)        
        return out

# Data paths
generator_folder = "/home/speechlab/Desktop/Jalansh/NAM2WHSPR_Results_CycleGAN/Generator_Res"
discriminator_folder = "/home/speechlab/Desktop/Jalansh/NAM2WHSPR_Results_CycleGAN/Discriminator_Res"

train_data = speech_data("/home/speechlab/Desktop/Jalansh/CSTR-NAM-TIMIT-Plus/NAM_feats/mat/training_batches")
train_dataloader = DataLoader(dataset=train_data, batch_size=1, shuffle=True, num_workers=2)
val_data = speech_data("/home/speechlab/Desktop/Jalansh/CSTR-NAM-TIMIT-Plus/NAM_feats/mat/validation_batches")
val_dataloader = DataLoader(dataset=val_data, batch_size=1, shuffle=True, num_workers=2)

# Path for test data
test_data = "/home/speechlab/Desktop/Jalansh/CSTR-NAM-TIMIT-Plus/NAM_feats/mat/testing_batches"

# Initialization of Generators and Discriminators
# G_AB = nam -> whisper
# G_BA = whisper -> nam
G_AB = Generator(40, 40)
G_BA = Generator(40, 40)

D_A = Discriminator(40, 1)
D_B = Discriminator(40, 1)

# Losse functions
criterion_GAN = nn.MSELoss()
criterion_cycle = nn.L1Loss()
criterion_identity = nn.L1Loss()

if cuda:
    G_AB = G_AB.cuda()
    G_BA = G_BA.cuda()
    D_A = D_A.cuda()
    D_B = D_B.cuda()
    #mmse_loss.cuda()
    #adversarial_loss.cuda()
    criterion_GAN.cuda()
    criterion_cycle.cuda()
    criterion_identity.cuda()


#Optimizers
optimizer_G = torch.optim.Adam(itertools.chain(G_AB.parameters(), G_BA.parameters()), lr = learning_rate)#, betas=(b1, b2))
optimizer_D_A = torch.optim.Adam(D_A.parameters(), lr = learning_rate)# , betas = (b1, b2))
optimizer_D_B = torch.optim.Adam(D_B.parameters(), lr = learning_rate)# , betas = (b1, b2))

## Learning rate update schedulers
#lr_scheduler_G = torch.optim.lr_scheduler.LambdaLR(optimizer_G, lr_lambda = [0,1])#LambdaLR(num_epochs, 0, decay_epoch).step)
#lr_scheduler_D_A = torch.optim.lr_scheduler.LambdaLR(optimizer_D_A, lr_lambda = LambdaLR(num_epochs, 0, decay_epoch).step)
#lr_scheduler_D_B = torch.optim.lr_scheduler.LambdaLR(optimizer_D_B, lr_lambda=LambdaLR(num_epochs, epoch, decay_epoch).step)

Tensor = torch.cuda.FloatTensor if cuda else torch.FloatTensor

# Buffers of previously generated samples
#generated_nam_buffer = ReplayBuffer()
#generated_whisper_buffer = ReplayBuffer()


# Training function
def training(data_loader, epoch):
    G_AB.train()
    G_BA.train()
    D_A.train()
    D_B.train()
    
    for en, (nam, whisper) in enumerate(data_loader):
        nam = Variable(nam.squeeze(0), ).cuda() if cuda else Variable(nam.squeeze(0))
        whisper = Variable(whisper.squeeze(0)).cuda() if cuda else Variable(whisper.squeeze(0))
        nam = nam.type(Tensor)
        whisper = whisper.type(Tensor)
        
        # print(whisper.shape)  #1 x 1000 x 40
        valid = Variable(Tensor(whisper.shape[0], 1).fill_(1.0), requires_grad=False).cuda() if cuda else Variable(Tensor(whisper.shape[0], 1).fill_(1.0), requires_grad=False)
        fake = Variable(Tensor(whisper.shape[0], 1).fill_(0.0), requires_grad=False).cuda() if cuda else Variable(Tensor(whisper.shape[0], 1).fill_(0.0), requires_grad=False)
        
        #----Generator Training----
        optimizer_G.zero_grad()
        # print(nam.type())
        
        # Identity loss
        loss_id_A = criterion_identity(G_BA(nam), nam)
        loss_id_B = criterion_identity(G_AB(whisper), whisper)
        loss_identity = (loss_id_A + loss_id_B) / 2
        
        # GAN loss
        generated_whisper = G_AB(nam)
        loss_GAN_AB = criterion_GAN(D_B(generated_whisper), valid)
        
        generated_nam = G_BA(whisper)
        loss_GAN_BA = criterion_GAN(D_A(generated_nam), valid)
        
        loss_GAN = (loss_GAN_AB + loss_GAN_BA) / 2
        
        # Cycle-consistence loss
        recov_nam = G_BA(generated_whisper)
        loss_cycle_A = criterion_cycle(recov_nam, nam)
        
        recov_whisper = G_AB(generated_nam)
        loss_cycle_B = criterion_cycle(recov_whisper, whisper)

        loss_cycle = (loss_cycle_A + loss_cycle_B) / 2

        # Total loss
        loss_G = loss_GAN + lambda_cyc * loss_cycle + lambda_id * loss_identity
        
        loss_G.backward(retain_graph = True)
        optimizer_G.step()
        
        # -------------------------------------
        # Discriminator-A Training
        optimizer_D_A.zero_grad()

        # Real loss
        loss_real = criterion_GAN(D_A(nam), valid)
        
        # Fake loss (on batch of previously generated samples)
        #generated_nam_ = generated_nam_buffer.push_and_pop(generated_nam)
        loss_fake = criterion_GAN(D_A(generated_nam.detach()), fake)
        
        # Total loss
        loss_D_A = (loss_real + loss_fake) / 2

        loss_D_A.backward()
        optimizer_D_A.step()
        
        
        # Discriminator B Training
        optimizer_D_B.zero_grad()
        
        # Real loss
        loss_real = criterion_GAN(D_B(whisper), valid)
        
        # Fake loss (on batch of previously generated samples)
        loss_fake = criterion_GAN(D_B(generated_whisper.detach()), fake)

        # Total loss
        loss_D_B = (loss_real + loss_fake) / 2

        loss_D_B.backward()
        optimizer_D_B.step()

        #loss_D = (loss_D_A + loss_D_B) / 2     
        print("[Epoch %d/%d] [Iteration %d/%d] [Discriminator-A Loss: %f] [Discriminator-B Loss: %f] [Generator Loss: %f]" % (epoch, num_epochs, en+1, 
                 len(data_loader), loss_D_A, loss_D_B, loss_G))

# Validation function
def validating(data_loader):
    G_AB.eval()
    G_BA.eval()
    D_A.eval()
    D_B.eval()
    discriminator_running_loss_1 = 0
    discriminator_running_loss_2 = 0
    generator_running_loss = 0
    
    for en, (nam, whisper) in enumerate(data_loader):
        nam = Variable(nam.squeeze(0)).cuda() if cuda else Variable(nam.squeeze(0))
        whisper = Variable(whisper.squeeze(0)).cuda() if cuda else Variable(whisper.squeeze(0))
        nam = nam.type(Tensor)
        whisper = whisper.type(Tensor)

        valid = Variable(Tensor(whisper.shape[0], 1).fill_(1.0), requires_grad=False).cuda() if cuda else Variable(Tensor(whisper.shape[0], 1).fill_(1.0), requires_grad=False)
        fake = Variable(Tensor(whisper.shape[0], 1).fill_(0.0), requires_grad=False).cuda() if cuda else Variable(Tensor(whisper.shape[0], 1).fill_(0.0), requires_grad=False)
        
        #----Generator ----

        # Identity loss
        loss_id_A = criterion_identity(G_BA(nam), nam)
        loss_id_B = criterion_identity(G_AB(whisper), whisper)
        loss_identity = (loss_id_A + loss_id_B) / 2
        
        # GAN loss
        generated_whisper = G_AB(nam)
        loss_GAN_AB = criterion_GAN(D_B(generated_whisper), valid)
        
        generated_nam = G_BA(whisper)
        loss_GAN_BA = criterion_GAN(D_A(generated_nam), valid)
        
        loss_GAN = (loss_GAN_AB + loss_GAN_BA) / 2
        
        # Cycle loss
        recov_nam = G_BA(generated_whisper)
        loss_cycle_A = criterion_cycle(recov_nam, nam)
        
        recov_whisper = G_AB(generated_nam)
        loss_cycle_B = criterion_cycle(recov_whisper, whisper)

        loss_cycle = (loss_cycle_A + loss_cycle_B) / 2

        # Total loss
        loss_G = loss_GAN + lambda_cyc * loss_cycle + lambda_id * loss_identity
        
        #----Discriminator-A 
        loss_real = criterion_GAN(D_A(nam), valid)
        
        # Fake loss (on batch of previously generated samples)
        #generated_nam_ = generated_nam_buffer.push_and_pop(generated_nam)
        loss_fake = criterion_GAN(D_A(generated_nam.detach()), fake)
        
        # Total loss
        loss_D_A = (loss_real + loss_fake) / 2
        
        # Discriminator B Training        
        # Real loss
        loss_real = criterion_GAN(D_B(whisper), valid)
        
        # Fake loss (on batch of previously generated samples)
        #generated_whisper_ = generated_whisper_buffer.push_and_pop(generated_whisper)
        loss_fake = criterion_GAN(D_B(generated_whisper.detach()), fake)

        # Total loss
        loss_D_B = (loss_real + loss_fake) / 2

        generator_running_loss += loss_G.item()
        discriminator_running_loss_1 += loss_D_A.item()
        discriminator_running_loss_2 += loss_D_B.item()
        
    return generator_running_loss/(en+1), discriminator_running_loss_1/(en+1), discriminator_running_loss_2/(en+1)


# Start training
generator_loss_plot = []
discriminator_loss_plot_1 = []
discriminator_loss_plot_2 = []

print("------------TRAINING------------")

for i in range(num_epochs):
    training(train_dataloader, i+1)
    if (i+1)%5 == 0:
        torch.save(G_AB, join(generator_folder, "Generator_AB_Epoch_{}.pth".format(i+1)))
        torch.save(G_BA, join(generator_folder, "Generator_BA_Epoch_{}.pth".format(i+1)))
        torch.save(D_A, join(discriminator_folder, "Discriminator_A_Epoch_{}.pth".format(i+1)))
        torch.save(D_B, join(discriminator_folder, "Discriminator_B_Epoch_{}.pth".format(i+1)))
    
    generator_loss, discriminator_loss_1, discriminator_loss_2 = validating(val_dataloader)
    generator_loss_plot.append(generator_loss)
    discriminator_loss_plot_1.append(discriminator_loss_1)
    discriminator_loss_plot_2.append(discriminator_loss_2)

#     if i == 0:
#         gplot = viz.line(Y=np.array([generator_loss]), X=np.array([i]), opts=dict(title='VGAN_Generator_Jalansh'))
#         dplot = viz.line(Y=np.array(discriminator_loss), X=np.array([i]), opts=dict(title='VGAN_Discriminator_Jalansh'))
#     else:
#         viz.line(Y=np.array([generator_loss]), X=np.array([i]), win=gplot, update='append')
#         viz.line(Y=np.array([discriminator_loss]), X=np.array([i]), win=dplot, update='append')

    print("[Epoch %d/%d] [Discriminator-A Loss: %f] [Discriminator-B Loss: %f] [Generator Loss: %f]" % (i+1, num_epochs, 
                                                                           discriminator_loss_1, discriminator_loss_2, generator_loss))
savemat(generator_folder + "/" + str('Generator_loss.mat'), mdict={'foo': generator_loss_plot})
savemat(discriminator_folder + "/" + str('Discriminator-A_loss.mat'), mdict={'foo': discriminator_loss_plot_1})
savemat(discriminator_folder + "/" + str('Discriminator-B_loss.mat'), mdict={'foo': discriminator_loss_plot_2})

plt.figure()
plt.title('Generator Loss')
plt.plot(generator_loss_plot)
plt.savefig('Generator Loss.png')
plt.figure()
plt.title('Discriminator-A Loss')
plt.plot(discriminator_loss_plot_1)
plt.savefig('Discriminator-A_Loss.png')
plt.figure()
plt.title('Discriminator-B Loss')
plt.plot(discriminator_loss_plot_2)
plt.savefig('Discriminator-B_Loss.png')
print("---------------------------TRAINING COMPLETED---------------------------")

#Testing
print("Testing phase")
result_folder = "/home/speechlab/Desktop/Jalansh/NAM2WHSPR_Results"
n = len(listdir(test_data))
trained_model = torch.load("/home/speechlab/Desktop/Jalansh/NAM2WHSPR_Results_CycleGAN/Generator_Res/Generator_AB_Epoch_150.pth")
testing_results = "/home/speechlab/Desktop/Jalansh/NAM2WHSPR_Results_CycleGAN/Testing_results"

for i in range(n):
    matfile = loadmat(join(test_data, "Test_Batch_{}.mat".format(str(i))))
    
    nam = torch.from_numpy(matfile['Feat'])
    #print(nam.shape)
    nam = Variable(nam.type(Tensor))
    print("nam: " + str(nam.shape))
    predicted_whisper = trained_model(nam)
#     print("converted file: " + str(predicted_whisper.shape))
    savemat(join(testing_results, 'Test_Batch_{}'.format(str(i))), mdict={'foo': predicted_whisper.cpu().data.numpy() if cuda else predicted_whisper.data.numpy()})
