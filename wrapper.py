import subprocess
import pandas as pd

class P1_Wrapper:
    def __init__(self, beta= 1.0, sigma= 1.0, gamma=0.1,
               n_steps= 1000, s0=0.99, e0= 0.01, i0=0.0, r0 = 0.0):
        
        self.beta = beta
        self.sigma = sigma
        self.gamma = gamma
        self.n_steps = n_steps
        self.s0 = s0
        self.e0 = e0
        self.i0 = i0
        self.r0 = r0
    
    def run(self):
        command = ["./seir_sim", "P1",
                   str(self.beta), str(self.sigma), str(self.gamma),
                   str(self.n_steps), str(self.s0), str(self.e0), str(self.i0), str(self.r0)]

        result = subprocess.run(command, capture_output=True, text=True)
        return result


class P2_Wrapper:
    def __init__(self, beta=1.0, sigma = 0.1, gamma = 0.005, N=250, 
                 seed=1234):
        self.beta = beta
        self.sigma = sigma 
        self.gamma = gamma
        self.N = N
        self.seed = seed

    def run(self):
        command = ["./seir_sim", "P2",
                   str(self.beta), str(self.sigma), str(self.gamma),
                   str(self.N), str(self.seed)]
        result = subprocess.run(command, capture_output=True, text=True)
        return result

