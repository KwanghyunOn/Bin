import torch
from torchvision import transforms
from efficientnet_pytorch import EfficientNet
import config as cfg
from utils import load_dataset

model = EfficientNet.from_pretrained('efficientnet-b0')

tfms = transforms.Compose([transforms.Resize(224),
                           transforms.ToTensor(), 
                           transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225]),])

train_dataset = load_dataset('train', transform=tfms)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=cfg.batch_size, shuffle=True, num_workers=cfg.num_workers)
optimizer = torch.optim.Adam(model.parameters(), lr=cfg.lr)
criterion = torch.nn.CrossEntropyLoss()

device = torch.device("cuda:0")
model.train()

for epoch in range(cfg.num_epochs):
    for inputs, labels in train_loader:
        inputs = inputs.to(device)
        labels = labels.to(device)
        logits = model(inputs)
        loss = criterion(logits, labels)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    torch.save(model.state_dict(), osp.join(cfg.model_dir, f'snapshot_{epoch}.pth.tar'))
