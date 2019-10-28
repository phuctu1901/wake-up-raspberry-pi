# I. Nguyên tắc hoạt động:

Trên mạch Raspberry Pi có chân reset, cho phép khởi động lại mạch Pi từ trạng thái tắt bằng cách cấp tín hiệu ở mức thấp cho chân này trong thời gian ngắn. Bằng cách sử dụng Arduino + Mạch tín hiệu thời gian thực DS1307, chúng ta có thể biết được thời gian để bật. Khi thời gian đến, ghi chân D3 từ Arduino với mức tín hiệu thấp trong thời gian ngắn (1s), từ đó sẽ reset mạch Raspberry Pi.

Sử dụng giao tiếp i2c giữa mạch Raspberry Pi và mạch Arduino để thiết lập thời gian cho mạch bật tắt.

Với cách làm này, có thể thiết lập được nhiều chế độ bật tắt ví dụ như thứ 7, chủ nhật không cần bật...

# II. Cách thức thực hiện:

## 1. Linh kiện:
- Arduino Nano: 1 cái.
- DS1307 : 1 cái.
- Jump và dây cắm đực cái.

## 2. Thực hiện: 

 *Bước 1*: Nối Arduino, DS1307 với nhau qua giao tiếp I2C, đồng thời nối luôn với Raspberry Pi.

 *Bước 2*: Cấp nguồn cho Arduino bằng chân out 5v trên Raspberry tới chân 5v của Arduino.

 *Bước 3*: Cấp nguồn cho mạch DS1307 (nguồn 5v)

 *Bước 4*: Nối chân D3 của Arduino với chân RESET(RUN) không cần nối chân GND vì mạch dùng chung 1 nguồn.

 *Bước 5*: Nạp code cho Arduino.

 *Bước 6*: Cấu hình trước khi hoạt động:
    
1. Kích hoạt i2c
2. Tắt chức năng power up thông qua gpio03:
```bash
sudo nano /boot/config.txt
```
Bỏ chú thích dòng hoặc thêm mới nếu chưa có :
```
dtoverlay=gpio-poweroff
```
 *Bước 7*: Kiểm tra:
 ```bash
 sudo i2cdetect -y 1
 ```
Nếu hiện địa chỉ của ds1307, arduino là phần cứng đã ok.

# III. Hướng dẫn sử dụng:


## 1. Hẹn giờ tắt:
```bash
sudo nano /etc/crontab
```

```
mm hh * * * root poweroff
```
Trong đó mm là phút, hh là giờ sẽ tắt.

## 2. Hẹn giờ bật:
```
python3 i2c.py
```
Nhập nội dung:
```
w1202
```
Trong đó 12 là giờ, 02 là phút, nhớ là phải ghi đủ w[hh][mm], nếu ghi w122 thì sẽ bị lỗi.

3. Kiểm tra thời gian trên mạch DS1307:

a. Kiểm tra thời gian trên mạch:

b. Nạp lại thời gian:

