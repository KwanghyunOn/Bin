import torch
from torch import nn
from torch.utils.data import Dataset, DataLoader
import torch.nn.functional as F
import numpy as np
import matplotlib.pyplot as plt


class RNN(nn.Module):
    def __init__(self, hidden_size=16):
        super(RNN, self).__init__()
        self.gru = nn.GRU(1, hidden_size, 1)
        self.fc = nn.Linear(hidden_size, 1)

    def forward(self, x, h0=None):
        y, h = self.gru(x, h0)
        y = self.fc(y)
        return y, h


class SeriesDataset(Dataset):
    def __init__(self, npy_path, train):
        self.data = np.load(npy_path).astype(np.float32)
        self.data = self.data.reshape(self.data.shape[0], -1)  # N x 10
        self.train = train

    def __len__(self):
        return self.data.shape[0]

    def __getitem__(self, idx):
        if self.train:
            return self.data[idx, :-1], self.data[idx, 1:]
        else:
            return self.data[idx, :5], self.data[idx, 5:]


device = torch.device('cuda')

train_dataset = SeriesDataset("./train_series.npy", train=True)
test_dataset = SeriesDataset("./test_series.npy", train=False)
train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=64)

model = RNN()
model.to(device)
optim = torch.optim.Adam(lr=3e-4, params=model.parameters())
loss_fn = nn.MSELoss()

model.train()
epoch_num = 50
loss_history = []
for epoch in range(epoch_num):
    loss_sum = 0.0
    for x, y in train_loader:
        x = x.to(device)
        y = y.to(device)
        x = x.unsqueeze(-1).permute(1,0,2)  # N x S -> S x N x 1
        y = y.unsqueeze(-1).permute(1,0,2)
        pred, _ = model(x)
        loss = loss_fn(pred, y)
        optim.zero_grad()
        loss.backward()
        optim.step()
        loss_sum += loss.item()
    loss_avg = loss_sum / len(train_loader)
    loss_history.append(loss_avg)
    print(f"epoch {epoch:02d}: {loss_avg:.3f}")

plt.plot(loss_history)
plt.savefig("loss_graph.png")

model.eval()
mape = 0.0
for x, y in test_loader:
    x = x.to(device)
    y = y.to(device)
    x = x.unsqueeze(-1).permute(1,0,2)
    out, h = model(x)
    out = out[-1].unsqueeze(0)
    preds = []
    preds.append(out)
    for _ in range(4):
        out, h = model(out, h)
        preds.append(out)
    pred = torch.cat(preds, 0).squeeze().T  # S x N x 1 -> N x S
    mape += ((pred - y) / y).abs().sum()
mape *= 100 / (len(test_dataset) * 5)
print(f"MAPE: {mape:.2f}%")

param_num = sum(p.numel() for p in model.parameters() if p.requires_grad)
print("parameter number: ", param_num)