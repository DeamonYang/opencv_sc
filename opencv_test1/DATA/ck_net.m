ObjDir = 'F:\sc_opencv\resheep\train\';%Ŀ��ͼƬ�ļ���·��  
OutputDir = 'E:\test2\';%����ļ���·��  
tnum = 3;%Ŀ��ͼƬ��Ŀ  
  
%ע��  
%  Ŀ��ͼƬ����Ϊ:i.png(iȡ1��tnum)  
  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
i = 1;

%for i = 0:1:83 
    
   
    bgFile = [ObjDir,int2str(i),'.jpg'];% ����ͼƬ������·��  
      
    Background = imread(bgFile); % ����ͼƬ���ҶȻ�  
    
    prsz = Background;
 %   prsz = imresize(Background,0.5);
    
     figure(2),imshow(prsz);
     %˳ʱ��90��
      prsz = imrotate(prsz,-90);
     figure(3),imshow(prsz);
      prsz = flipdim(prsz,2);
      figure(7),imshow(prsz);
    
    [m,n,l] = size(prsz);
    %matlab ͼ������Ϊ���к���
    rp = reshape(prsz,m*n,l);
    
%     HY = 100;
%     BASE = 320*HY;
%     rp = rp(1+BASE:320*5+BASE,1:3);
    
%     rp = reshape(rp,320,5,3);
%     figure(4),imshow(rp),title('�޸ĺ��ͼ��')
    
    rp(:,[1,end]) = fliplr(rp(:,[1,end]));
    
    rp = reshape(rp,4800,1);
    rp = double(rp);
    tag = myNeuralNetworkFunction(rp)
    
    %err = tag - mynetres(i)
    prsz = imrotate(prsz,90);
    figure(5),imshow(prsz);
    HY = 240-HY+3;
    line([tag,tag],[HY-5,HY+5],'Color','g','LineWidth',1);
    line([tag-5,tag+5],[HY,HY],'Color','g','LineWidth',1);
   
    
    
    pause(5);
      
 %   saveas(i,[OutputDir,int2str(i),'_bw.png']);%��������ͼƬ���浽Ŀ���ļ���  
%end 
