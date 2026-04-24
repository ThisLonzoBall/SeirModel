from wrapper import P1_Wrapper, P2_Wrapper

model1 = P1_Wrapper(beta= 1.0, sigma =1.0, gamma= 0.1, n_steps =1000)
model1.run()

model2 = P2_Wrapper(beta=1.0, sigma =0.1, gamma = 0.005, N=250)
model2.run()