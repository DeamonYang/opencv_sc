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
%��������  
  
ObjDir = 'F:\sc_opencv\seldata\';%Ŀ��ͼƬ�ļ���·��  
OutputDir = 'E:\test2\';%����ļ���·��  
tnum = 3;%Ŀ��ͼƬ��Ŀ  
  
% % % %ע��  
% % % %  Ŀ��ͼƬ����Ϊ:i.png(iȡ1��tnum)  
% % %   
% % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
% % % i = 472;
% % % 
% % % for i = 372:1:372+40 
% % %     
% % % 
% % %     bgFile = [ObjDir,int2str(i),'.jpg'];% ����ͼƬ������·��  
% % %       
% % %     Background = imread(bgFile); % ����ͼƬ���ҶȻ�  
% % %     
% % %     prsz = imresize(Background,0.5);
% % %     
% % % %     figure(2),imshow(prsz);
% % % %     %˳ʱ��90��
% % %      prsz = imrotate(prsz,-90);
% % %      figure(3),imshow(prsz);
% % %     
% % %     [m,n,l] = size(prsz);
% % %     %matlab ͼ������Ϊ���к���
% % %     rp = reshape(prsz,m*n,l);
% % %     
% % %     HY = 100;
% % %     BASE = 320*HY;
% % %     rp = rp(1+BASE:320*5+BASE,1:3);
% % %     
% % %     rp = reshape(rp,320,5,3);
% % %     figure(4),imshow(rp),title('�޸ĺ��ͼ��')
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
% % % %     figure(i+1),imshow(rp),title('�޸ĺ��ͼ��')
% % % %     rp = reshape(rp,5,320,3);
% % % %     figure(i+1),imshow(rp),title('�޸ĺ��ͼ��')
% % % %     
% % % %     rp = reshape(rp,4800,1);
% % % %     
% % % %     rp = double(rp);
% % % %     
% % % %     %����������
% % % %     tag = myNeuralNetworkFunction(rp);
% % % %     
% % % %     rp = uint8(rp);
% % % %     
% % % % 
% % % %     
% % % %     line([tag,tag],[123-5,123+5],'Color','g','LineWidth',1);
% % % %     line([tag-5,tag+5],[123,123],'Color','g','LineWidth',1);
% % % %     
% % % % %    figure(i),imshow(Background),title('�޸ĺ��ͼ��')  
% % %     
% % %     pause(5);
% % %       
% % %  %   saveas(i,[OutputDir,int2str(i),'_bw.png']);%��������ͼƬ���浽Ŀ���ļ���  
% % % end 



