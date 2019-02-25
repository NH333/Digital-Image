img = imread('C:\Users\NH3\Desktop\数字图像处理\image3-2.jpg');
img_size = size(img);
figure('Name','原图');
% img = imresize(img,0.5);
imshow(img);

img_fft = fft2(log(double(img) + 1));
img_fftshift = fftshift(img_fft);
figure('Name','fft');
imshow(img_fftshift);

%%%%%%%%%%%%%%%%% 这一段参数可调 %%%%%%%%%%%%%%%%%%%%%%%%
D0 = 2000;   %max = (768/2)^2
rH = 1;
rL = 0.15;
c = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

M = img_size(2) / 2;    %(M,N)为频谱图像的中心点
N = img_size(1) / 2;
H = zeros(img_size(1),img_size(2));
for v = 1:img_size(2)
    for u = 1:img_size(1)
        H(u,v) = (rH - rL) * (1 - (exp( -c * ((u-M)^2+(v-N)^2) / (D0^2)))) + rL;
    end
end
img_homo_pinyu = img_fftshift .* H;
img_homo_real = real(ifft2(ifftshift(img_homo_pinyu)) - 1);  
img_homo_kongyu = exp(img_homo_real);  %结果偏灰，灰度级过于集中，想到直方图均衡化

img_result = histeq(img_homo_kongyu);  %之前已经写过直方图均衡了，现在直接调用


figure('Name','同态结果+直方图均衡');
imshow(img_result);


        
