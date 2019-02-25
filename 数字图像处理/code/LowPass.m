img = imread('C:\Users\NH3\Desktop\数字图像处理\image2-1.jpg');
img = rgb2gray(img); 
figure(2);
imshow(img);
  
img_fft = fft2(img);
img_fftshift = fftshift(img_fft);


figure(1);
imshow(log(abs(img_fftshift)),[]);

  
img_size = size(img_fftshift);
N = img_size(1)/2;
M = img_size(2)/2;

%%%%%%%%%%%%%%%%%%%%%%%%%%理想低通滤波%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for n = 1:img_size(1)
    for m = 1:img_size(2)
        dist = sqrt(abs(m - M)*abs(m - M)+ abs(n - N)*abs(n - N));
		if (dist > 45 )
			img_fftshift(n,m) = 0;	
        end
    end
end
figure(3)
imshow(log(abs(img_fftshift)),[]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


img1 = ifftshift(img_fftshift);
img2 = ifft2(img1);
img = uint8(real(img2));
figure(4);
imshow(img);

			