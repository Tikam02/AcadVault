clc;
clear all;
close all;

% Reading an image
img = imread('download_grey.jpeg');


% Display image
figure(1)
imshow(img);
title('Original Image');

% Write image with another namee
imwrite(img, 'image2.jpeg');

% Image Info
disp('Image Info: ');
disp(imfinfo('image.jpeg'));

% Convert dataclass of gray image
img2=cast(img>75,'uint8').*img;
figure(2)
subplot(1,3,1);
imshow(img2);
title('Input image','FontSize',8);

img3=cast(img2,'double');
subplot(1,3,2);
imshow(img3);
title('Datatype class : Double','FontSize',8);

img4=cast(img2,'logical');
subplot(1,3,3);
imshow(img4);
title('Datatype class: Logical','FontSize',8);

% Convert image from one type to another
% Convert gray to binary image
figure(3)
img_bin=255*(img/127);
imshow(img_bin);
title('Original to binary');

% Flip image
% Horizontal
img_flipped_horizontal = img(:,(end:-1:1),:);
figure(4)
subplot(1, 2, 1);
imshow(img_flipped_horizontal);
title('Horizontal Flipped Image');

% Flip  image
% Vertical
img_flipped_vertical = img((end:-1:1),:,:);
subplot(1, 2, 2);
imshow(img_flipped_vertical);
title('Vertical Flipped Image');

figure(5)
subplot(2, 3, 1)
imshow(img);
title('Original Image');

subplot(2, 3, 2)
imshow(img);
title('Flipped horizontal (Image 2)');

% Addition
subplot(2, 3, 3)
imshow(img+img_flipped_horizontal);
title('Addition');

% Subtraction
subplot(2, 3, 4)
imshow(img-img_flipped_horizontal);
title('Subtraction');

% Multiplication
subplot(2, 3, 5)
imshow(img.*img_flipped_horizontal);
title('Multiplication');

% Division
subplot(2, 3, 6)
imshow(img./img_flipped_horizontal);
title('Division');

% Perform relational operations on color images
figure(7)
subplot(3,3,1);
imshow(img);
title('Input image 1','FontSize',8);

subplot(3,3,3);
imshow(img_flipped_horizontal);
title('Input image 2','FontSize',8);

subplot(3,3,4);
out=img==img_flipped_horizontal;
out=255*cast(out,'uint8');
imshow(out);
title('== operator','FontSize',8);

subplot(3,3,5);
out=img<img_flipped_horizontal;
out=255*cast(out,'uint8');
imshow(out);
title('< operator','FontSize',8);

subplot(3,3,6);
out=img>img_flipped_horizontal;
out=255*cast(out,'uint8');
imshow(out);
title('> operator','FontSize',8);

subplot(3,3,7);
out=img>=img_flipped_horizontal;
out=255*cast(out,'uint8');
imshow(out);
title('>= operator','FontSize',8);

subplot(3,3,8);
out=img<=img_flipped_horizontal;
out=255*cast(out,'uint8');
imshow(out);
title('<= operator','FontSize',8);

subplot(3,3,9);
out=img~=img_flipped_horizontal;
imshow(out);
title('~= operator','FontSize',8);

% Logial Operators
img_75=cast(img>75,'uint8').*img;
img_horizontal_flipped_75=cast(img_flipped_horizontal>75,'uint8').*img_flipped_horizontal;

figure(8)

subplot(3,2,1);
imshow(img_75);
title('Input image 1','FontSize',8);

subplot(3,2,3);
imshow(img_horizontal_flipped_75);
title('Input image 2','FontSize',8);

subplot(3,2,4);
out=img_75&img_horizontal_flipped_75;
out=255*cast(out,'uint8');
imshow(out);
title('AND operator','FontSize',8);

subplot(3,2,5);
out=img_75|img_horizontal_flipped_75;
out=255*cast(out,'uint8');
imshow(out);
title('OR operator','FontSize',8);

subplot(3,2,6);
out=~img_75;
out=255*cast(out,'uint8');
imshow(out);
title('NOT operator on Input 1','FontSize',8);

% Average value of image with conditional loop

n=numel(img);
img_doub=cast(img,'double');
avg=0;
for i=1:n
    avg=avg+img_doub(i);
end
avg=avg/n;
disp('Avg: ');
disp(avg);

% Extract subimage from given image
top_left=input('Enter top-left corner: ');
bottom_right=input('Enter bottom-right corner: ');
figure(9)
subplot(1, 2, 1);
title('Original Image');
imshow(img);
subplot(1, 2, 2);
img_sub = img(top_left(1):bottom_right(1),top_left(2):bottom_right(2), :);
imshow(img_sub);
title(['(',num2str(top_left(1)),',',num2str(top_left(2)),') to (',num2str(bottom_right(1)),',',num2str(bottom_right(2)),')'],'FontSize',8);
