img = imread('C:\Users\NH3\Desktop\����ͼ����\image3-2.jpg');
img_size = size(img);
figure('Name','ԭͼ');
% img = imresize(img,0.5);
imshow(img);

img_fft = fft2(log(double(img) + 1));
img_fftshift = fftshift(img_fft);
figure('Name','fft');
imshow(img_fftshift);

%%%%%%%%%%%%%%%%% ��һ�β����ɵ� %%%%%%%%%%%%%%%%%%%%%%%%
D0 = 2000;   %max = (768/2)^2
rH = 1;
rL = 0.15;
c = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

M = img_size(2) / 2;    %(M,N)ΪƵ��ͼ������ĵ�
N = img_size(1) / 2;
H = zeros(img_size(1),img_size(2));
for v = 1:img_size(2)
    for u = 1:img_size(1)
        H(u,v) = (rH - rL) * (1 - (exp( -c * ((u-M)^2+(v-N)^2) / (D0^2)))) + rL;
    end
end
img_homo_pinyu = img_fftshift .* H;
img_homo_real = real(ifft2(ifftshift(img_homo_pinyu)) - 1);  
img_homo_kongyu = exp(img_homo_real);  %���ƫ�ң��Ҷȼ����ڼ��У��뵽ֱ��ͼ���⻯

img_result = histeq(img_homo_kongyu);  %֮ǰ�Ѿ�д��ֱ��ͼ�����ˣ�����ֱ�ӵ���


figure('Name','̬ͬ���+ֱ��ͼ����');
imshow(img_result);


        
