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

def put_option(rate, strike_price, answer = ans):
    put_option_price = []
    delta = []
    B = []
    answer = ans.reverse()
    for i in range(len(answer)):
        if i==0:
            current = []
            for val in answer[0]:
                current.append(max(0,strike_price-val))
            put_option_price.append(current)
        else:
            current_delta = []
            current_put = []
            current_borrow = []
            for j in range(len(answer[i])):
                init_s = ans[i][j]
                su = ans[i+1][2*j]
                sd = ans[i+1][2*j+1]
                ps = put_option_price[-1][2*j]
                pd = put_option_price[-1][2*j+1]
                
                d = (ps - pd)/(su - sd)
                b = (ps + pd - d*(su + sd))/(2*(1+rate))
                
                current_put.append(d*init_s+b)
                current_delta.append(d)
                current_borrow.append(b)
            
            put_option_price.append(current_put)
            B.append(current_borrow)
            delta.append(current_delta)
    
if __name__=='__main__':
    s0,u,d,k,r,n = map(float, input().split())
    n = int(n)
    ans.append([s0])
    generate_binomial_pricing_of_stock(s0,u,d,n)
    put_option(rate = r, strike_price = k, answer = ans)
    for i in range(len(delta)-1, -1, -1):
        for val in delta[i]:
            print("{0:.6f}".format(val), end=' ')
        print()
    for i in range(len(B)-1, -1, -1):
        for val in B[i]:
            print("{0:.6f}".format(val), end=' ')
        print()