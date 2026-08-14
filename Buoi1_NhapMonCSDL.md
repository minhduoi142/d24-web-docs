# [Buổi 1] Nhập môn CSDL

> Tài liệu chuẩn bị trước buổi học CLB

---

## 1. CSDL là gì?

**CSDL (Cơ sở dữ liệu - Database)** là một tập hợp dữ liệu có tổ chức, được lưu trữ và truy xuất một cách có hệ thống trên máy tính, thường liên quan đến một chủ đề hoặc mục đích cụ thể (ví dụ: quản lý sinh viên, quản lý bán hàng, quản lý ngân hàng...).

### Đặc điểm của CSDL
- **Có cấu trúc**: dữ liệu được tổ chức theo bảng (table), gồm các dòng (row/record) và cột (column/field).
- **Liên kết với nhau**: các bảng dữ liệu có thể có quan hệ (relationship) với nhau, ví dụ bảng `Sinh viên` liên kết với bảng `Lớp học`.
- **Dùng chung**: nhiều người, nhiều ứng dụng có thể truy cập và sử dụng cùng một CSDL.
- **Toàn vẹn dữ liệu**: có các ràng buộc (constraint) để đảm bảo dữ liệu chính xác, nhất quán.
- **Bảo mật**: có cơ chế phân quyền truy cập (ai được đọc, ghi, sửa, xóa).

### Ví dụ thực tế
- CSDL quản lý sinh viên: lưu thông tin sinh viên, lớp học, điểm số.
- CSDL của sàn thương mại điện tử: lưu thông tin sản phẩm, đơn hàng, khách hàng.
- CSDL của ngân hàng: lưu thông tin tài khoản, giao dịch.

### Lợi ích khi dùng CSDL (so với lưu file thông thường như Excel, txt)
| Lưu file thông thường | Dùng CSDL |
|---|---|
| Dễ trùng lặp dữ liệu | Hạn chế trùng lặp (chuẩn hóa dữ liệu) |
| Khó truy vấn dữ liệu lớn | Truy vấn nhanh, mạnh mẽ bằng SQL |
| Khó chia sẻ nhiều người dùng cùng lúc | Hỗ trợ nhiều người dùng truy cập đồng thời |
| Không kiểm soát tính toàn vẹn | Có ràng buộc đảm bảo dữ liệu đúng, nhất quán |
| Bảo mật kém | Có cơ chế phân quyền, bảo mật |

---

## 2. Hệ quản trị CSDL là gì?

**Hệ quản trị CSDL (DBMS - Database Management System)** là một phần mềm dùng để tạo, quản lý, thao tác (thêm/sửa/xóa/truy vấn) và bảo vệ dữ liệu trong CSDL.

Nói cách khác: **CSDL** là "kho dữ liệu", còn **DBMS** là "công cụ/phần mềm" giúp con người và ứng dụng làm việc với kho dữ liệu đó.

### Chức năng chính của DBMS
1. **Định nghĩa dữ liệu**: tạo cấu trúc bảng, kiểu dữ liệu, ràng buộc.
2. **Thao tác dữ liệu**: thêm (INSERT), sửa (UPDATE), xóa (DELETE), truy vấn (SELECT).
3. **Quản lý giao dịch (Transaction)**: đảm bảo các thao tác thực hiện đúng, an toàn (ví dụ chuyển khoản ngân hàng).
4. **Bảo mật & phân quyền**: quản lý ai được truy cập, thao tác gì trên dữ liệu.
5. **Sao lưu & phục hồi (Backup & Restore)**: đề phòng mất dữ liệu do sự cố.
6. **Đảm bảo tính toàn vẹn & nhất quán dữ liệu**.

### Một số hệ quản trị CSDL phổ biến
- **Microsoft SQL Server** (MS SQL Server)
- **MySQL**
- **PostgreSQL**
- **Oracle Database**
- **SQLite**
- **MongoDB** (CSDL phi quan hệ - NoSQL)


---

## 3. Cài đặt MS SQL Server

### Các thành phần cần cài đặt
Để làm việc với MS SQL Server, cần cài **2 phần**:
1. **SQL Server** (bản Express - miễn phí, đủ dùng để học): đây là "bộ máy" DBMS thực sự xử lý dữ liệu.
2. **SQL Server Management Studio (SSMS)**: đây là công cụ giao diện (GUI) giúp thao tác với SQL Server dễ dàng hơn (viết câu lệnh, xem bảng, quản lý CSDL trực quan).
---

## 4. Câu lệnh tạo Database, Table trong MS SQL Server

### 4.1. Tạo Database

Cú pháp:
```sql
CREATE DATABASE TenDatabase;
```

Ví dụ: tạo CSDL quản lý sinh viên
```sql
CREATE DATABASE QuanLySinhVien;
```

Chọn database để làm việc (rất quan trọng, nếu không sẽ tạo bảng nhầm database khác):
```sql
USE QuanLySinhVien;
```

Xóa database (nếu cần):
```sql
DROP DATABASE QuanLySinhVien;
```

### 4.2. Tạo Table

Cú pháp tổng quát:
```sql
CREATE TABLE TenBang (
    TenCot1 KieuDuLieu RangBuoc,
    TenCot2 KieuDuLieu RangBuoc,
    ...
);
```

Ví dụ: tạo bảng `SinhVien`
```sql
CREATE TABLE SinhVien (
    MaSV INT PRIMARY KEY IDENTITY(1,1),   -- Mã sinh viên, tự tăng
    HoTen NVARCHAR(100) NOT NULL,          -- Họ tên, không được để trống
    NgaySinh DATE,                         -- Ngày sinh
    GioiTinh NVARCHAR(10),                 -- Giới tính
    Email VARCHAR(100) UNIQUE,             -- Email, không trùng nhau
    MaLop INT                              -- Mã lớp (sẽ liên kết với bảng Lớp)
);
```

Ví dụ: tạo bảng `Lop` và thiết lập khóa ngoại (Foreign Key) liên kết với bảng `SinhVien`
```sql
CREATE TABLE Lop (
    MaLop INT PRIMARY KEY IDENTITY(1,1),
    TenLop NVARCHAR(50) NOT NULL
);

ALTER TABLE SinhVien
ADD CONSTRAINT FK_SinhVien_Lop
FOREIGN KEY (MaLop) REFERENCES Lop(MaLop);
```

### 4.3. Một số kiểu dữ liệu thường dùng trong SQL Server
| Kiểu dữ liệu | Mô tả |
|---|---|
| `INT` | Số nguyên |
| `FLOAT`, `DECIMAL(m,n)` | Số thực |
| `VARCHAR(n)` | Chuỗi ký tự (không dấu tiếng Việt tốt) |
| `NVARCHAR(n)` | Chuỗi ký tự (hỗ trợ Unicode, nên dùng cho tiếng Việt) |
| `DATE` | Ngày tháng |
| `DATETIME` | Ngày giờ |
| `BIT` | Kiểu boolean (0/1 - đúng/sai) |

### 4.4. Một số ràng buộc (Constraint) thường dùng
| Ràng buộc | Ý nghĩa |
|---|---|
| `PRIMARY KEY` | Khóa chính, xác định duy nhất mỗi dòng dữ liệu |
| `FOREIGN KEY` | Khóa ngoại, liên kết với bảng khác |
| `NOT NULL` | Không được để trống |
| `UNIQUE` | Giá trị không được trùng lặp |
| `DEFAULT` | Giá trị mặc định nếu không nhập |
| `IDENTITY(1,1)` | Tự động tăng giá trị (bắt đầu từ 1, tăng mỗi lần 1) |

### 4.5. Xem cấu trúc và xóa bảng
```sql
-- Xem toàn bộ bảng đang có trong database
SELECT * FROM INFORMATION_SCHEMA.TABLES;

-- Xóa bảng
DROP TABLE SinhVien;
```

---