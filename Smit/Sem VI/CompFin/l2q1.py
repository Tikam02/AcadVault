def generate_binomial_pricing_of_stock(S0, d, u, n):
    stock_prices = [float(S0)]
    j = 0
    for i in range(int(n)):
        new_stock = []
        while j<len(stock_prices):
            new_stock.append(float(stock_prices[j]*d))
            new_stock.append(float(stock_prices[j]*u))
            j+=1
        for k in new_stock:
            stock_prices.append(float(k))
    return stock_prices

S0, d, u, n = map(float, input().split())
stock_prices = generate_binomial_pricing_of_stock(S0, d, u, n)
new_line = 1
i = 0
while i<len(stock_prices):
    for k in range(new_line):
        if i < len(stock_prices):
            print("{0:.6f}".format(stock_prices[i]), end = " ")
        i+=1
    new_line*=2
    print()
    