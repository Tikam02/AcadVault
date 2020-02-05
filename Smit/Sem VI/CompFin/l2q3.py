import random

ans = []

def generate_binomial_pricing_of_stock(S0,u,d,n):
    if n == 0:
        return
    curr = []
    for val in ans[-1]:
        curr.append(val*u)
        curr.append(val*d)
    ans.append(curr)
    generate_binomial_pricing_of_stock(S0,u,d,n-1)

def call_option_pricing(rate, strike_price, answer = ans):    
    call_option_price = []
    delta = []
    B = [] 
    for i in range(len(answer)-1, -1, -1):
        if i==len(answer)-1:
            current = []
            for val in answer[i]:
                current.append(max(0,val-strike_price))
            call_option_price.append(current)
        else:
            current_borrow = []
            current_delta = []
            current_put = []
            for j in range(len(answer[i])):
                s0 = answer[i][j]
                su = answer[i+1][2*j]
                sd = answer[i+1][2*j+1]
                ps = call_option_price[-1][2*j]
                pd = call_option_price[-1][2*j+1]
                
                d = (ps - pd)/(su - sd)
                b = (ps + pd - d*(su + sd))/(2*(1+rate))
                
                current_borrow.append(b)
                current_delta.append(d)
                current_put.append(d*s0+b)
            
            B.append(current_borrow)
            call_option_price.append(current_put)
            delta.append(current_delta)

    return B, call_option_price, delta


def monte_carlo_simulation(s0, u, d, strike_price, rate, n, s, N):
    random.seed(s)
    avg_price=0
    for i in range(N):
        price = s0
        for j in range(n):
            prob = random.random()
            p = (1+rate-d)/(u-d)
            if(prob>p):
                price*=u
            else:
                price*=d
        price = max(price-strike_price,0) 
        avg_price+=price
    avg_price /= N
    avg_price /= pow((1+rate),n)
    return avg_price

s0,u,d,k,r,n,s,N = map(float, input().split())
n = int(n)
N = int(N)
ans.append([s0])
generate_binomial_pricing_of_stock(s0, u, d, n)
avg_price = monte_carlo_simulation(s0,u,d,k,r,n,s,N)
B, call_option_price, delta = call_option_pricing(r,k)


print("{0:.6f}".format(call_option_price[-1][0]),end=' ')
print("{0:.6f}".format(avg_price))