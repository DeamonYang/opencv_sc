load('ck_result.mat')
load('ckpic.mat')
x = ckpic;
mynetres = myNeuralNetworkFunction(x);
plot(mynetres,'r')
hold on;
plot(ck_result,'g');
err = ck_result - mynetres;
plot(err,'b');

%PIC1_RES = myNeuralNetworkFunction(pic111)



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
%参数配置  
  
ObjDir = 'F:\sc_opencv\seldata\';%目标图片文件夹路径  
OutputDir = 'E:\test2\';%输出文件夹路径  
tnum = 3;%目标图片数目  
  
% % % %注：  
% % % %  目标图片命名为:i.png(i取1到tnum)  
% % %   
% % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
% % % i = 472;
% % % 
% % % for i = 372:1:372+40 
% % %     
% % % 
% % %     bgFile = [ObjDir,int2str(i),'.jpg'];% 读入图片的完整路径  
% % %       
% % %     Background = imread(bgFile); % 读入图片、灰度化  
% % %     
% % %     prsz = imresize(Background,0.5);
% % %     
% % % %     figure(2),imshow(prsz);
% % % %     %顺时针90度
% % %      prsz = imrotate(prsz,-90);
% % %      figure(3),imshow(prsz);
% % %     
% % %     [m,n,l] = size(prsz);
% % %     %matlab 图像排列为先列后行
% % %     rp = reshape(prsz,m*n,l);
% % %     
% % %     HY = 100;
% % %     BASE = 320*HY;
% % %     rp = rp(1+BASE:320*5+BASE,1:3);
% % %     
% % %     rp = reshape(rp,320,5,3);
% % %     figure(4),imshow(rp),title('修改后的图像')
% % %     
% % %     rp = reshape(rp,4800,1);
% % %     rp = double(rp);
% % %     tag = myNeuralNetworkFunction(rp)
% % %     prsz = imrotate(prsz,90);
% % %     figure(5),imshow(prsz);
% % %     HY = 240-HY+3;
% % %     line([tag,tag],[HY-5,HY+5],'Color','g','LineWidth',1);
% % %     line([tag-5,tag+5],[HY,HY],'Color','g','LineWidth',1);
% % %    
% % %     
% % % %     rp = reshape(rp,320,5,3);
% % % %     figure(i+1),imshow(rp),title('修改后的图像')
% % % %     rp = reshape(rp,5,320,3);
% % % %     figure(i+1),imshow(rp),title('修改后的图像')
% % % %     
% % % %     rp = reshape(rp,4800,1);
% % % %     
% % % %     rp = double(rp);
% % % %     
% % % %     %调用神经网络
% % % %     tag = myNeuralNetworkFunction(rp);
% % % %     
% % % %     rp = uint8(rp);
% % % %     
% % % % 
% % % %     
% % % %     line([tag,tag],[123-5,123+5],'Color','g','LineWidth',1);
% % % %     line([tag-5,tag+5],[123,123],'Color','g','LineWidth',1);
% % % %     
% % % % %    figure(i),imshow(Background),title('修改后的图像')  
% % %     
% % %     pause(5);
% % %       
% % %  %   saveas(i,[OutputDir,int2str(i),'_bw.png']);%将处理后的图片保存到目标文件夹  
% % % end 



