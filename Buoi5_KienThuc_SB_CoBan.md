# Buổi 5 – Kiến Thức Spring Boot Cơ Bản & Nền Tảng Web Backend
## HTTP/HTTPS | RESTful API | IoC & DI

---

## PHẦN 1: TỔNG QUAN GIAO THỨC HTTP & HTTPS

### 1.1. HTTP là gì?
**HTTP (HyperText Transfer Protocol - Giao thức truyền tải siêu văn bản)** là giao thức tầng ứng dụng (Application Layer), hoạt động trên nền tảng bộ giao thức TCP/IP, dùng để trao đổi dữ liệu giữa **Client** (Trình duyệt, Mobile App, Postman...) và **Server** (Spring Boot, Node.js, Web Server...).

```
┌─────────────────┐       1. HTTP Request (Gửi yêu cầu)        ┌─────────────────┐
│                 │ ─────────────────────────────────────────► │                 │
│  Client / User  │                                            │  Backend Server │
│ (Browser/App)   │ ◄───────────────────────────────────────── │  (Spring Boot)  │
└─────────────────┘       2. HTTP Response (Trả kết quả)       └─────────────────┘
```

### 1.2. Đặc tính cốt lõi của HTTP
- **Stateless (Phi trạng thái):**
  - Mỗi Request là hoàn toàn độc lập, Server **không tự động nhớ** trạng thái hay dữ liệu của Request trước đó.
  - *Giải pháp duy trì trạng thái đăng nhập:* Sử dụng **Session - Cookie** (truyền thống) hoặc **JWT Token (JSON Web Token)** đính kèm trong Header `Authorization` (chuẩn RESTful hiện đại).
- **Client - Server Model:** Phân tách rạch ròi trách nhiệm giữa giao diện người dùng (Frontend) và xử lý dữ liệu/nghiệp vụ (Backend).
- **Media Independent (Linh hoạt định dạng):** Có thể truyền tải bất kỳ định dạng nào (JSON, XML, HTML, Image, Video, Multipart/Form-data) thông qua Header `Content-Type`.

### 1.3. Phân biệt HTTP vs HTTPS
- **HTTP (Cổng 80):** Dữ liệu truyền đi dưới dạng văn bản thô (**Plain text**), không được mã hóa $\rightarrow$ Dễ bị kẻ xấu nghe lén (Sniffing) hoặc giả mạo (Man-in-the-Middle).
- **HTTPS (Cổng 443 - HTTP Secure):** Là HTTP được bảo vệ bằng lớp mã hóa **SSL/TLS (Secure Sockets Layer / Transport Layer Security)**:
  - **Mã hóa (Encryption):** Kết hợp mã hóa bất đối xứng (RSA/ECC) khi bắt tay kết nối (**SSL Handshake**) và mã hóa đối xứng (AES) trong quá trình truyền dữ liệu.
  - **Toàn vẹn (Data Integrity):** Dữ liệu không thể bị thay đổi trên đường truyền.
  - **Xác thực (Authentication):** Sử dụng chứng chỉ số (**SSL Certificate**) để Client xác minh chính xác danh tính của Server.

---

## PHẦN 2: CÁC HTTP METHODS & TÍNH CHẤT IDEMPOTENT

HTTP Method thể hiện **mục đích hành động** mà Client muốn thực hiện trên tài nguyên (Resource).

### 2.1. Bảng so sánh các HTTP Methods thông dụng

| Method | Ý nghĩa nghiệp vụ | Request Body | Safe (An toàn)? | Idempotent (Bất biến)? |
|:---|:---|:---:|:---:|:---:|
| **GET** | Đọc/Lấy dữ liệu tài nguyên | ❌ Không | ✅ Có | ✅ Có |
| **POST** | Tạo mới một tài nguyên | ✅ Có | ❌ Không | ❌ Không |
| **PUT** | Cập nhật **toàn bộ** tài nguyên (thay thế) | ✅ Có | ❌ Không | ✅ Có |
| **PATCH** | Cập nhật **một phần** tài nguyên (1 vài trường) | ✅ Có | ❌ Không | ❌ Không (thường) |
| **DELETE** | Xóa tài nguyên | ❌ Không (thường) | ❌ Không | ✅ Có |
| **HEAD** | Lấy Headers (giống GET nhưng không trả Body) | ❌ Không | ✅ Có | ✅ Có |
| **OPTIONS**| Kiểm tra Method & CORS server hỗ trợ | ❌ Không | ✅ Có | ✅ Có |

> **Khái niệm then chốt:**
> - **Safe (An toàn):** Truy vấn không làm biến đổi bất kỳ dữ liệu nào trên Server (chỉ đọc).
> - **Idempotent (Bất biến/Nhất quán):** Gọi 1 lần hay gọi $N$ lần liên tiếp với cùng tham số thì **trạng thái dữ liệu cuối cùng trên Server vẫn như nhau**.
>   - `DELETE /students/5`: Gọi lần 1 xóa student id=5; gọi lần 2, 3 kết quả trên DB vẫn là student id=5 đã bị xóa $\rightarrow$ Idempotent.
>   - `POST /students`: Gọi 3 lần sẽ tạo ra 3 bản ghi khác nhau $\rightarrow$ Non-Idempotent.

### 2.2. Phân biệt chi tiết giữa PUT và PATCH

```
Giả sử bản ghi ban đầu: Student { id: 5, name: "Nguyen Van A", age: 20, email: "a@gmail.com" }

- Gửi PUT /students/5 với Body: { "name": "Nguyen Van B" }
  -> PUT thay thế toàn bộ bản ghi: Các trường không gửi (age, email) sẽ bị gán null/mất dữ liệu.
  -> Kết quả: { id: 5, name: "Nguyen Van B", age: null, email: null }

- Gửi PATCH /students/5 với Body: { "name": "Nguyen Van B" }
  -> PATCH chỉ cập nhật trường 'name', giữ nguyên 'age' và 'email'.
  -> Kết quả: { id: 5, name: "Nguyen Van B", age: 20, email: "a@gmail.com" }
```

---

## PHẦN 3: CẤU TRÚC HTTP REQUEST, RESPONSE & STATUS CODES

### 3.1. Cấu tạo của một HTTP Request
Một gói tin Request do Client gửi lên Server bao gồm 4 thành phần:

```http
POST /api/v1/students?notify=true HTTP/1.1              <--- [1] Request Line (Method + URI + HTTP Version)
Host: api.example.com                                   <--- [2] Headers (Metadata)
Content-Type: application/json
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI...
User-Agent: Mozilla/5.0

{                                                       <--- [3] Request Body (Payload dữ liệu)
  "name": "Tran Van B",
  "age": 21,
  "email": "b.tran@gmail.com"
}
```

*4 vị trí truyền dữ liệu từ Client lên Server:*
1. **Path Variable (Định danh tài nguyên):** `/students/{id}` $\rightarrow$ `/students/5`.
2. **Query Parameters (Tìm kiếm, phân trang, lọc):** `/students?page=1&size=20&sort=name,asc`.
3. **Request Headers (Metadata, Auth Token, Content-Type):** `Authorization: Bearer <token>`.
4. **Request Body (Payload lớn dạng JSON/Form-data):** Dùng cho `POST`, `PUT`, `PATCH`.

---

### 3.2. Cấu tạo của một HTTP Response
Gói tin Response do Server trả về cho Client gồm 3 thành phần:

```http
HTTP/1.1 201 Created                                    <--- [1] Status Line (Version + Status Code + Reason)
Content-Type: application/json                          <--- [2] Response Headers
Date: Fri, 11 Sep 2026 07:49:00 GMT

{                                                       <--- [3] Response Body (Dữ liệu trả về)
  "id": 10,
  "name": "Tran Van B",
  "age": 21,
  "email": "b.tran@gmail.com"
}
```

---

### 3.3. Các mã HTTP Status Codes quan trọng cần nhớ

```
┌───────┬─────────────────────────────────────────────────────────────────────────────┐
│ Nhóm  │ Ý nghĩa tổng quan                                                           │
├───────┼─────────────────────────────────────────────────────────────────────────────┤
│ 1xx   │ Informational (Thông tin - Server đã nhận request, đang tiếp tục xử lý)     │
│ 2xx   │ Success (Thành công - Request đã được xử lý trọn vẹn)                       │
│ 3xx   │ Redirection (Chuyển hướng - Client cần thực hiện hành động bổ sung)         │
│ 4xx   │ Client Error (Lỗi phía Client - Request sai cú pháp, thiếu quyền truy cập)  │
│ 5xx   │ Server Error (Lỗi phía Server - Server gặp lỗi nội bộ, crash, sập database) │
└───────┴─────────────────────────────────────────────────────────────────────────────┘
```

#### Nhóm 2xx (Thành công):
- `200 OK`: Xử lý thành công (thường dùng cho GET, PUT, PATCH).
- `201 Created`: Tạo mới tài nguyên thành công (thường dùng cho POST).
- `204 No Content`: Xử lý thành công nhưng không có dữ liệu trả về trong Body (thường dùng cho DELETE).

#### Nhóm 3xx (Chuyển hướng & Cache):
- `301 Moved Permanently`: Tài nguyên đã chuyển vĩnh viễn sang URL mới.
- `304 Not Modified`: Dữ liệu không thay đổi so với bản cache của trình duyệt $\rightarrow$ Tiết kiệm băng thông.

#### Nhóm 4xx (Lỗi từ phía Client - Cực kỳ quan trọng trong Backend):
- `400 Bad Request`: Request gửi sai cú pháp JSON hoặc sai kiểu dữ liệu.
- `401 Unauthorized (Chính xác: Unauthenticated)`: **Chưa đăng nhập** (thiếu Token hoặc Token hết hạn/sai).
- `403 Forbidden`: **Không đủ quyền hạn** (Đã đăng nhập thành công với Role `USER` nhưng cố tình gọi API của `ADMIN`).
- `404 Not Found`: Không tìm thấy URI hoặc tài nguyên (ID không tồn tại).
- `405 Method Not Allowed`: Gọi sai Method (ví dụ: URL chỉ nhận `POST` nhưng Client lại gửi `GET`).
- `409 Conflict`: Xung đột dữ liệu (ví dụ: đăng ký tài khoản với Email đã tồn tại).
- `422 Unprocessable Entity`: Cú pháp JSON đúng nhưng vi phạm Validation nghiệp vụ (ví dụ: tuổi < 0, email không đúng định dạng).

#### Nhóm 5xx (Lỗi từ phía Server):
- `500 Internal Server Error`: Lỗi logic code chưa được bắt (`NullPointerException`, lỗi tính toán...).
- `502 Bad Gateway`: Server Gateway / Nginx nhận phản hồi lỗi từ Backend app.
- `503 Service Unavailable`: Server đang quá tải hoặc tạm thời bảo trì.
- `504 Gateway Timeout`: Server trung gian chờ Backend phản hồi quá lâu dẫn đến hết thời gian (Timeout).

---

## PHẦN 4: THIẾT KẾ RESTFUL API CHUẨN QUỐC TẾ

### 4.1. REST và RESTful API là gì?
- **REST (REpresentational State Transfer):** Là kiểu kiến trúc thiết kế API do Roy Fielding đề xuất năm 2000, lấy **Tài nguyên (Resource)** làm trung tâm và dùng các HTTP Method chuẩn để thao tác.
- **RESTful API:** Là API tuân thủ đầy đủ các nguyên tắc của REST.

### 4.2. Các quy tắc vàng khi thiết kế RESTful API

#### 1. Sử dụng Danh từ số nhiều cho Resource URI (KHÔNG dùng Động từ)
```http
-- ❌ SAI (Theo kiểu RPC/Action):
GET  /getAllStudents
POST /createStudent
POST /updateStudent?id=5
POST /deleteStudent/5

-- ✅ ĐÚNG CHUẨN REST (URI là Danh từ định danh tài nguyên, Method là hành động):
GET    /students          -> Lấy danh sách sinh viên
GET    /students/5        -> Lấy chi tiết sinh viên có id = 5
POST   /students          -> Tạo mới sinh viên
PUT    /students/5        -> Cập nhật toàn bộ thông tin sinh viên id = 5
PATCH  /students/5        -> Cập nhật 1 vài trường sinh viên id = 5
DELETE /students/5        -> Xóa sinh viên id = 5
```

#### 2. Thể hiện quan hệ lồng nhau (Nested Resources) hợp lý
```http
GET  /students/5/courses      -> Lấy danh sách khóa học của sinh viên id = 5
POST /students/5/courses/10   -> Đăng ký môn học id = 10 cho sinh viên id = 5
```

#### 3. Chuẩn hóa Phân trang (Pagination) & Sắp xếp (Sorting)
```http
GET /students?page=0&size=20&sort=name,asc
```

#### 4. Chuẩn hóa định dạng Response (ApiResponse Wrapper)
Trong dự án thực tế, các API luôn trả về cấu trúc thống nhất:

```json
{
  "success": true,
  "code": 200,
  "message": "Get student details successfully",
  "data": {
    "id": 5,
    "name": "Nguyen Van A",
    "email": "a.nguyen@gmail.com"
  },
  "timestamp": "2026-09-11T07:49:00.123Z"
}
```

---

## PHẦN 5: DESIGN PATTERN – DI & IoC TRONG SPRING

### 5.1. Vấn đề của cách tiếp cận truyền thống (Tight Coupling)

```java
// ❌ Cách truyền thống: Class tự "new" trực tiếp dependency của nó
public class OrderService {
    private MySQLOrderRepository orderRepository = new MySQLOrderRepository();
    private VnPayPaymentService paymentService = new VnPayPaymentService();

    public void processOrder(Order order) {
        orderRepository.save(order);
        paymentService.pay(order.getAmount());
    }
}
```
* **Hạn chế:** `OrderService` bị gắn chặt vào `MySQLOrderRepository`. Muốn chuyển sang PostgreSQL hoặc mock dữ liệu để viết Unit Test gần như là không thể $\rightarrow$ Vi phạm nguyên lý **Dependency Inversion** (chữ D trong SOLID).

---

### 5.2. IoC (Inversion of Control - Đảo ngược quyền điều khiển)

- **Nguyên lý IoC:** Lập trình viên không tự mình khởi tạo (`new`), cấu hình và quản lý vòng đời đối tượng nữa. Toàn bộ quyền điều khiển đó được **chuyển giao cho Spring IoC Container (ApplicationContext)**.
- **Hollywood Principle:** *"Don't call us, we'll call you"* (Đừng tự đi tìm phụ thuộc, Container sẽ mang phụ thuộc đến cho bạn).

```
Cách truyền thống:   [ OrderService ] ─── Tự 'new' ───► [ MySQLOrderRepository ]
                            
Cách dùng IoC:       [ Spring IoC Container ]
                            │
               Tự động tạo & "tiêm" vào (Inject)
                            ▼
                     [ OrderService ] ◄── Nhận ── [ OrderRepository (Interface) ]
```

---

### 5.3. DI (Dependency Injection - Tiêm phụ thuộc)

**DI** là kỹ thuật cụ thể để hiện thực hóa nguyên lý **IoC**: Spring Container tự động cung cấp (tiêm) các đối tượng phụ thuộc vào class cần sử dụng.

#### 3 cách triển khai DI trong Spring:

#### 1. Constructor Injection (Khuyến nghị dùng 100% trong thực tế)
```java
@Service
public class OrderService {
    private final OrderRepository orderRepository; // Bất biến (Immutable)
    private final PaymentService paymentService;

    // Từ Spring 4.3+, class chỉ có 1 constructor không cần thêm @Autowired
    public OrderService(OrderRepository orderRepository, PaymentService paymentService) {
        this.orderRepository = orderRepository;
        this.paymentService = paymentService;
    }
}
```
* **Ưu điểm:**
  - Khai báo trường `final` $\rightarrow$ Đảm bảo an toàn đa luồng (Thread-safe).
  - Dễ dàng Unit Test độc lập (`new OrderService(mockRepo, mockPayment)`).
  - Tránh lỗi `NullPointerException` lúc runtime.
  - Giúp phát hiện sớm lỗi phụ thuộc vòng (**Circular Dependency**) ngay khi ứng dụng khởi động.

#### 2. Setter Injection (Dùng cho dependency tùy chọn - Optional)
```java
@Service
public class OrderService {
    private NotificationService notificationService;

    @Autowired
    public void setNotificationService(NotificationService notificationService) {
        this.notificationService = notificationService;
    }
}
```

#### 3. Field Injection (KHÔNG KHUYẾN KHÍCH - Bad Practice)
```java
@Service
public class OrderService {
    @Autowired
    private OrderRepository orderRepository; // Tiêm trực tiếp vào private field
}
```
* **Nhược điểm:** Không thể đặt `final`, khó test độc lập nếu không dùng Mockito Reflection, ẩn giấu sự phình to của dependencies.

---

