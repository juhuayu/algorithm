import torch
import  torch.nn as nn
in_data = torch.Tensor([[1.0], [2.0], [3.0],[16.0],[8.0]])
study_data = torch.Tensor([[2.0], [4.0], [6.0],[32.0],[16.0]])  #in_data * 2

class LinearModel(torch.nn.Module): 
    def __init__(self):
        super(LinearModel, self).__init__() 
        self.model = nn.Sequential(
            nn.Linear(1, 5),
            nn.ReLU(),
            nn.Linear(5, 1),
        )
    def forward(self, x): 
        y_pred = self.model(x) 
        return y_pred
    
model = LinearModel()
criterion = torch.nn.MSELoss(size_average=False)
optimizer = torch.optim.SGD(model.parameters(), lr=0.0001)

for epoch in range(1000):
    m = model(in_data)
    loss = criterion(m, study_data) 
    print(epoch, loss.item())
    
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    

test_data = torch.Tensor([[4.0],[5.0],[7.0],[150.0],[32.0],[9.0]]) 
test_out = model(test_data) 
print('test_out = ', test_out.data)