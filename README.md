# Ứng dụng Quản lý Bệnh viện (Hospital Management System - HMS)

Đây là một hệ thống quản lý bệnh viện hoàn chỉnh được viết 100% bằng C++, chạy trên nền tảng Console, áp dụng các tính năng hướng đối tượng (OOP) và sử dụng file Text (`.txt`) để lưu trữ dữ liệu bền vững.

## Tính năng chính (Modules)

1. **Quản lý Nhân viên**: Bác sĩ, Y tá, Admin. Thêm, sửa, xóa, tìm kiếm nhân viên.
2. **Quản lý Bệnh nhân**: Thông tin bệnh nhân cơ bản và tiền sử bệnh.
3. **Quản lý Lịch khám**: Lịch hẹn giữa bác sĩ và bệnh nhân.
4. **Quản lý Điều trị**: Chẩn đoán, đơn thuốc, ghi chú điều trị.
5. **Quản lý Thuốc và Vật tư**: Quản lý kho thuốc, thiết bị y tế.
6. **Quản lý Hóa đơn**: Lập và thanh toán hóa đơn.
7. **Báo cáo và Thống kê**: Xem tổng doanh thu của bệnh viện.
8. **Quản trị Hệ thống**: Đăng nhập, thay đổi mật khẩu và đổi màu sắc giao diện Console.

## Cấu trúc thư mục

```text
Hospital_Management/
│
├── header/            # Chứa toàn bộ các file khai báo C++ (.h)
│   ├── models.h
│   ├── Utils.h
│   ├── App.h
│   └── ...
│
├── implementation/    # Chứa toàn bộ các file cài đặt logic C++ (.cpp)
│   ├── Utils.cpp
│   ├── App.cpp
│   └── ...
│
├── data/              # Chứa toàn bộ file text dữ liệu (.txt)
│   ├── employees.txt
│   ├── patients.txt
│   └── ...
│
├── main.cpp           # Điểm vào chính của ứng dụng
├── build.bat          # Script tự động biên dịch bằng g++
└── HMS.exe            # File thực thi của chương trình (sau khi biên dịch)
```

## Hướng dẫn Biên dịch (Dành cho Dev)

Nếu bạn có chỉnh sửa mã nguồn gốc, hãy làm theo các bước sau để biên dịch lại ứng dụng:

1. Đảm bảo máy tính đã được cài đặt trình biên dịch **MinGW (g++)**.
2. Bấm đúp vào file `build.bat` hoặc mở Terminal (PowerShell/CMD) tại thư mục chứa dự án và gõ lệnh:
   ```bat
   .\build.bat
   ```
3. Script sẽ tự động nối các thư mục, tạo ra file chạy có tên `HMS.exe`.

## Hướng dẫn Sử dụng (Dành cho Người dùng)

1. Mở file **`HMS.exe`** để khởi chạy chương trình.
2. Ở lần đầu tiên khởi chạy (hoặc khi file `data/employees.txt` trống), hệ thống sẽ cấp mặc định một tài khoản Admin để truy cập:
   - **Tên đăng nhập**: `admin`
   - **Mật khẩu**: `admin`
3. Tại giao diện chính, chương trình sẽ hiển thị các lựa chọn ứng với các Menu. Vui lòng **gõ các chữ số (0, 1, 2, 3...)** và nhấn phím **Enter** để chọn thao tác tương ứng.
4. Mỗi khi cần thêm dữ liệu, ứng dụng sẽ hiện ra các câu hỏi để bạn nhập vào.
5. Mọi dữ liệu bạn thêm mới sẽ được tự động đồng bộ và lưu vào thư mục `data/` an toàn!
6. *Mẹo nhỏ*: Bạn có thể vào phần **[8] Quản trị hệ thống** để đổi giao diện Console nếu thích (Ví dụ: nền trắng, chữ đen hoặc phong cách hacker matrix).

---

*Cảm ơn bạn đã sử dụng Hệ thống Quản lý Bệnh viện!*
