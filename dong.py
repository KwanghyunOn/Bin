import torch 
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
from torchvision import models

import socket
import pickle
import json
from timeit import default_timer as timer
import time

device = torch.device("cuda:0")

original_model = models.alexnet(pretrained=True)

print("Main model")
child_counter = 0
for child in original_model.children():
    print(" child", child_counter, "is:")
    print(child)
    child_counter += 1

class AlexNetConv4(nn.Module):
    def __init__(self):
        super(AlexNetConv4, self).__init__()
        self.features = nn.Sequential(
            # stop at conv4
            *list(original_model.features.children())[:]
        )
    def forward(self, x):
        x = self.features(x)
        return x

model1 = AlexNetConv4()
model1.to(device)

print("Mobile model")
child_counter = 0
for child in model1.children():
    print(" child", child_counter, "is:")
    print(child)
    child_counter += 1

print("{:6s}{:6s}".format("n","time"))
for n in [*range(1,10), *range(10,2000,10)]:
    images = torch.rand(n,3,224,224)
    images = images.to(device)

    iter_num = 3
    time_sum = 0.0
    for _ in range(iter_num):
        torch.cuda.synchronize(device=device)
        start=time.time()
        outputs1 = model1(images)
        torch.cuda.synchronize(device=device)
        end=time.time()
        time_sum += (end-start)
    print(f"{n:<6d}{time_sum/iter_num:6.4g}")

    # print(outputs1.shape)
    # print("time= " , end-start)
    #print(outputs1)