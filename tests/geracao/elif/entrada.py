def classifica(n):
    if n < 0:
        return "negativo"
    elif n == 0:
        return "zero"
    elif n < 10:
        return "pequeno"
    else:
        return "grande"

print(classifica(-3))
print(classifica(0))
print(classifica(5))
print(classifica(50))
x = 5
if x > 10:
    print(1)
elif x > 3:
    print(2)
print(3)
