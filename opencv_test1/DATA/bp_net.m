%[x,t] = simplefit_dataset;
load('res.mat');
load('rpic.mat');
x = rpic;
t = testdatares;
net = feedforwardnet(10);
net = train(net,x,t);
view(net);
y = net(x); %5.047228716184418
y1 = net(5.047228716184418);
perf = perform(net,y,t);
plot(y,'r');
hold on;
plot(t,'g');