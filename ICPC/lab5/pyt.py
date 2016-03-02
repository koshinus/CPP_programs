def func(yn, xn):
	return (-20.0)*yn*yn*(xn - 0.4)

def myAbs(x):
	if x > 0:
		return x
	else: 
		return -x

		
xi = 0.0 
yi = 0.5
limit = 1.0
step = 0.05 #здесь менять шаг

print(yi)
k1 = step*func(yi,xi)
k2 = step*func(yi + k1/2.0, xi + step/2.0)
k3 = step*func(yi + k2/2.0, xi + step/2.0)
k4 = step*func(yi + k3, xi + step)
yl = yi
xi = xi + step
ym = 1.0/6*k1 + 2.0/6*k2 + 2.0/6*k3 + 1.0/6*k4 + yl
print(ym)
yn = 0
while xi < limit:
	xi = xi + step
	while True:
		prevY = yn
		yn = yl + step/3*(func(prevY, xi + step) + 4*func(ym, xi) + func(yl, xi-step))
		if not myAbs(yn - prevY) > 0.000001:
			break
	print(yn)
	yl = ym
	ym = yn