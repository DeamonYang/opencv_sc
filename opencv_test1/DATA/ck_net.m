ObjDir = 'F:\sc_opencv\resheep\train\';%目标图片文件夹路径  
OutputDir = 'E:\test2\';%输出文件夹路径  
tnum = 3;%目标图片数目  
  
%注：  
%  目标图片命名为:i.png(i取1到tnum)  
  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
i = 1;

%for i = 0:1:83 
    
   
    bgFile = [ObjDir,int2str(i),'.jpg'];% 读入图片的完整路径  
      
    Background = imread(bgFile); % 读入图片、灰度化  
    
    prsz = Background;
 %   prsz = imresize(Background,0.5);
    
     figure(2),imshow(prsz);
     %顺时针90度
      prsz = imrotate(prsz,-90);
     figure(3),imshow(prsz);
      prsz = flipdim(prsz,2);
      figure(7),imshow(prsz);
    
    [m,n,l] = size(prsz);
    %matlab 图像排列为先列后行
    rp = reshape(prsz,m*n,l);
    
%     HY = 100;
%     BASE = 320*HY;
%     rp = rp(1+BASE:320*5+BASE,1:3);
    
%     rp = reshape(rp,320,5,3);
%     figure(4),imshow(rp),title('修改后的图像')
    
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
      
 %   saveas(i,[OutputDir,int2str(i),'_bw.png']);%将处理后的图片保存到目标文件夹  
%end 
