import torch
import torch.nn as nn
from torchvision import datasets, transforms

## 准确率：99.03%loss:0.001008

train_transform = transforms.Compose([
                                transforms.RandomAffine(degrees = 0,translate=(0.1, 0.1)),#对照片进行随机平移
                                transforms.RandomRotation((-10,10)),        #随机旋转
                                transforms.ToTensor(),
                                transforms.Normalize((0.1307,),(0.3081,))])
test_transform = transforms.Compose([transforms.ToTensor(),
                                    transforms.Normalize((0.1307,),(0.3081,))])

# 下载训练集
train_dataset = datasets.MNIST(root='./data/',train=True,transform=train_transform,download=True)
# 下载测试集
test_dataset = datasets.MNIST(root='./data/',train=False,transform=test_transform,download=True)

batch_size = 32
# 装载训练集
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,batch_size=batch_size,shuffle=True)  # type: ignore
# 装载测试集
test_loader = torch.utils.data.DataLoader(dataset=test_dataset,batch_size=batch_size,shuffle=True)  # type: ignore

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

class LinearModel(torch.nn.Module): 
    def __init__(self):
        super(LinearModel, self).__init__() 
        self.model = nn.Sequential(
            nn.Conv2d(1, 24, 5, padding=2),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(24, 200, 5),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(200, 400, 5),
            nn.ReLU(),
            nn.Flatten(start_dim=1, end_dim=-1),
            nn.Linear(400, 200),
            nn.ReLU(),
            nn.Linear(200, 50),
            nn.ReLU(),
            nn.Linear(50, 10)
        )
    def forward(self, x): 
        y = self.model(x)
        return y
    
model = LinearModel()
model.to(device)
criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.AdamW(model.parameters(), lr=0.001)
model.train()
for i in range(2):
    for batch_idx, (data, target) in enumerate(train_loader):
        data = data.to(device)
        target = target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = criterion(output, target)
        if batch_idx % 100 == 0:
            print("第%d轮,第%d次训练,loss:%f" % (i,batch_idx,loss.item()))
        loss.backward()
        optimizer.step()

print()
totalLoss = 0
correct = 0
model.train(False)
for index,(testImgs,labels) in enumerate(test_loader):
    testImgs = testImgs.to(device)
    labels = labels.to(device)
    outputs = model(testImgs)
    loss = criterion(outputs,labels)
    predictions = torch.argmax(outputs,dim = 1)
    temp = (predictions == labels).sum()
    correct += temp
    totalLoss += loss.item()
    accuracy = temp / len(labels)
    print("第%d次测试,准确率：%d%%,loss:%f" % (index,accuracy*100,loss.item()))
    
testCount = test_dataset.__len__()
print("准确率：%.2f%%loss:%f" % (correct/testCount*100,totalLoss/testCount)) 
