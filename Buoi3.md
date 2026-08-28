# [BUỔI 3] Ôn tập SQL cơ bản

---


## 1. Thao tác cơ bản: SELECT, INSERT, UPDATE, DELETE

### 1.1 SELECT — Truy vấn dữ liệu

```sql
-- Lấy tất cả cột
SELECT * FROM Customers;

-- Lấy các cột cụ thể
SELECT full_name, city FROM Customers;
```

### 1.2 AS — Đặt bí danh (alias)

Dùng để đổi tên cột hiển thị hoặc đặt tên tắt cho bảng khi viết truy vấn phức tạp.

```sql
SELECT
    full_name AS "Tên khách hàng",
    city AS "Thành phố"
FROM Customers AS c;
```

### 1.3 DISTINCT — Loại bỏ giá trị trùng lặp

```sql
-- Liệt kê các thành phố có khách hàng, không lặp lại
SELECT DISTINCT city FROM Customers;
```

Kết quả: `Ha Noi, Ho Chi Minh, Da Nang` (chỉ 3 dòng dù có 4 khách hàng).

### 1.4 INSERT — Thêm dữ liệu

```sql
INSERT INTO Customers (customer_id, full_name, email, city, created_at)
VALUES (5, 'Hoang Van E', 'e@gmail.com', 'Hue', '2024-05-01');
```

### 1.5 UPDATE — Cập nhật dữ liệu

```sql
-- Luôn nhớ mệnh đề WHERE, thiếu WHERE sẽ update toàn bộ bảng!
UPDATE Products
SET stock_quantity = stock_quantity - 1
WHERE product_id = 1;
```

### 1.6 DELETE — Xóa dữ liệu

```sql
-- Tương tự, thiếu WHERE sẽ xóa toàn bộ dữ liệu trong bảng
DELETE FROM Orders
WHERE status = 'Cancelled';
```

---

## 2. Lọc dữ liệu: WHERE, HAVING

### 2.1 WHERE — Lọc dòng trước khi nhóm/tổng hợp

Áp dụng cho từng dòng dữ liệu gốc, dùng được với các toán tử: `=, <>, >, <, >=, <=, BETWEEN, IN, LIKE, IS NULL, AND, OR`.

```sql
-- Sản phẩm có giá trên 15 triệu
SELECT product_name, price
FROM Products
WHERE price > 15000000;

-- Khách hàng ở Hà Nội hoặc Đà Nẵng
SELECT full_name, city
FROM Customers
WHERE city IN ('Ha Noi', 'Da Nang');

-- Sản phẩm hết hàng
SELECT product_name
FROM Products
WHERE stock_quantity = 0;

-- Tên sản phẩm chứa chữ "Mac"
SELECT product_name FROM Products WHERE product_name LIKE '%Mac%';
```

### 2.2 HAVING — Lọc SAU khi đã GROUP BY

`HAVING` dùng để lọc trên kết quả đã tổng hợp (SUM, COUNT, AVG...), còn `WHERE` không lọc được trên hàm tổng hợp.

```sql
-- Danh mục có tổng số sản phẩm > 1
SELECT category_id, COUNT(*) AS so_luong_san_pham
FROM Products
GROUP BY category_id
HAVING COUNT(*) > 1;
```

> ❗ Lỗi thường gặp: viết `WHERE COUNT(*) > 1` → SAI, vì `WHERE` chạy trước khi dữ liệu được nhóm nên chưa có `COUNT(*)` để lọc.

**Bài tập gợi ý:**
1. Lấy danh sách khách hàng có `created_at` sau ngày 2024-02-01.
2. Lấy danh sách các order có `status` khác `'Cancelled'`.
3. Tìm các khách hàng có tổng số đơn hàng >= 2 (dùng GROUP BY + HAVING).

---

## 3. Kết hợp bảng và kết quả: JOIN, UNION

### 3.1 INNER JOIN — Chỉ lấy dòng khớp ở cả 2 bảng

```sql
SELECT o.order_id, c.full_name, o.order_date
FROM Orders o
INNER JOIN Customers c ON o.customer_id = c.customer_id;
```

### 3.2 LEFT JOIN — Giữ toàn bộ bảng bên trái, kể cả không khớp

```sql
-- Liệt kê TẤT CẢ khách hàng, kể cả người chưa từng đặt hàng
SELECT c.full_name, o.order_id
FROM Customers c
LEFT JOIN Orders o ON c.customer_id = o.customer_id;
```
Khách hàng nào chưa có đơn hàng thì `order_id` sẽ là `NULL`.

### 3.3 RIGHT JOIN

Ngược lại LEFT JOIN, giữ toàn bộ bảng bên phải.

```sql
SELECT c.full_name, o.order_id
FROM Orders o
RIGHT JOIN Customers c ON o.customer_id = c.customer_id;
```

### 3.4 JOIN nhiều bảng

```sql
-- Chi tiết đơn hàng kèm tên khách hàng và tên sản phẩm
SELECT
    o.order_id,
    c.full_name,
    p.product_name,
    od.quantity,
    od.unit_price
FROM OrderDetails od
JOIN Orders o ON od.order_id = o.order_id
JOIN Customers c ON o.customer_id = c.customer_id
JOIN Products p ON od.product_id = p.product_id;
```

### 3.5 UNION / UNION ALL — Gộp kết quả 2 truy vấn

Yêu cầu: số cột và kiểu dữ liệu tương ứng phải giống nhau. `UNION` loại trùng, `UNION ALL` giữ trùng (nhanh hơn).

```sql
-- Gộp danh sách "liên hệ": khách hàng ở Hà Nội và khách hàng ở Đà Nẵng
SELECT full_name, city FROM Customers WHERE city = 'Ha Noi'
UNION
SELECT full_name, city FROM Customers WHERE city = 'Da Nang';
```


---

## 4. Tổng hợp và nhóm dữ liệu: COUNT, SUM, AVG, GROUP BY

### 4.1 Các hàm tổng hợp (Aggregate functions)

| Hàm | Ý nghĩa |
|---|---|
| `COUNT()` | Đếm số dòng |
| `SUM()` | Tính tổng |
| `AVG()` | Tính trung bình |
| `MAX()` / `MIN()` | Giá trị lớn nhất / nhỏ nhất |

```sql
-- Tổng số khách hàng
SELECT COUNT(*) AS tong_khach_hang FROM Customers;

-- Giá trung bình sản phẩm
SELECT AVG(price) AS gia_trung_binh FROM Products;

-- Sản phẩm đắt nhất và rẻ nhất
SELECT MAX(price) AS gia_max, MIN(price) AS gia_min FROM Products;
```

### 4.2 GROUP BY — Nhóm dữ liệu theo cột

```sql
-- Số lượng sản phẩm theo từng danh mục
SELECT category_id, COUNT(*) AS so_san_pham
FROM Products
GROUP BY category_id;

-- Tổng doanh thu theo từng đơn hàng
SELECT order_id, SUM(quantity * unit_price) AS thanh_tien
FROM OrderDetails
GROUP BY order_id;

-- Tổng số tiền mỗi khách hàng đã chi (JOIN + GROUP BY)
SELECT c.full_name, SUM(od.quantity * od.unit_price) AS tong_chi_tieu
FROM Customers c
JOIN Orders o ON c.customer_id = o.customer_id
JOIN OrderDetails od ON o.order_id = od.order_id
GROUP BY c.full_name;
```


---

## 5. Thứ tự thực thi logic của truy vấn (Query Execution Order)

Đây là phần **quan trọng nhất** để hiểu tại sao viết `WHERE` với hàm tổng hợp bị lỗi, hay tại sao alias ở `SELECT` không dùng được trong `WHERE`.

**Thứ tự viết (syntax order)** khác với **thứ tự thực thi (logical execution order)**:

```
1. FROM        -- xác định bảng nguồn
2. JOIN        -- kết hợp các bảng
3. WHERE       -- lọc dòng dữ liệu gốc
4. GROUP BY    -- nhóm dữ liệu
5. HAVING      -- lọc trên nhóm đã tổng hợp
6. SELECT      -- chọn cột / tính toán / đặt alias
7. DISTINCT    -- loại bỏ trùng lặp
8. ORDER BY    -- sắp xếp kết quả
9. LIMIT/OFFSET -- giới hạn số dòng trả về
```

**Ví dụ minh họa:**

```sql
SELECT c.city, COUNT(*) AS so_khach
FROM Customers c
WHERE c.created_at >= '2024-01-01'
GROUP BY c.city
HAVING COUNT(*) > 1
ORDER BY so_khach DESC;
```

Thực thi theo thứ tự:
1. `FROM Customers c` → lấy toàn bộ bảng.
2. `WHERE` → lọc các dòng có `created_at >= '2024-01-01'`.
3. `GROUP BY c.city` → nhóm các dòng còn lại theo thành phố.
4. `HAVING COUNT(*) > 1` → chỉ giữ nhóm có nhiều hơn 1 khách hàng.
5. `SELECT` → chọn `city` và tính `COUNT(*)`, đặt alias `so_khach`.
6. `ORDER BY so_khach DESC` → sắp xếp giảm dần.

> 💡 Vì `SELECT` chạy **sau** `WHERE`, nên alias đặt trong `SELECT` (vd: `so_khach`) không dùng được trong `WHERE`, nhưng dùng được trong `ORDER BY` (vì `ORDER BY` chạy sau `SELECT`).

---

## 6. Truy vấn con (Subquery)

### 6.1 Subquery trong WHERE

```sql
-- Khách hàng đã từng đặt hàng (dùng subquery trả về danh sách id)
SELECT full_name
FROM Customers
WHERE customer_id IN (
    SELECT DISTINCT customer_id FROM Orders
);

-- Sản phẩm có giá cao hơn giá trung bình
SELECT product_name, price
FROM Products
WHERE price > (SELECT AVG(price) FROM Products);
```

### 6.2 Subquery trong FROM (bảng tạm/derived table)

```sql
SELECT category_id, AVG(price) AS gia_tb
FROM (
    SELECT * FROM Products WHERE stock_quantity > 0
) AS available_products
GROUP BY category_id;
```

### 6.3 Subquery trong SELECT (correlated subquery)

```sql
-- Với mỗi khách hàng, đếm số đơn hàng của họ
SELECT
    c.full_name,
    (SELECT COUNT(*) FROM Orders o WHERE o.customer_id = c.customer_id) AS so_don_hang
FROM Customers c;
```

### 6.4 EXISTS / NOT EXISTS

```sql
-- Khách hàng CHƯA từng đặt hàng
SELECT full_name
FROM Customers c
WHERE NOT EXISTS (
    SELECT 1 FROM Orders o WHERE o.customer_id = c.customer_id
);
```

**So sánh nhanh JOIN vs Subquery:** JOIN thường hiệu quả hơn khi cần lấy dữ liệu từ nhiều bảng cùng lúc để hiển thị; Subquery phù hợp khi chỉ cần lọc/kiểm tra điều kiện dựa trên bảng khác mà không cần hiển thị cột của bảng đó.



---

## 8. Lỗi thường gặp cần lưu ý

| Lỗi | Nguyên nhân |
|---|---|
| `WHERE` dùng hàm tổng hợp (`WHERE COUNT(*) > 1`) | Sai thứ tự thực thi — phải dùng `HAVING` |
| Quên `WHERE` trong `UPDATE`/`DELETE` | Ảnh hưởng toàn bộ bảng — cực kỳ nguy hiểm |
| `SELECT` cột không nằm trong `GROUP BY` và không phải hàm tổng hợp | Vi phạm quy tắc GROUP BY (một số DB như MySQL cho phép ngầm nhưng kết quả không xác định) |
| Dùng alias của `SELECT` trong `WHERE` | `WHERE` chạy trước `SELECT` nên alias chưa tồn tại |
| `UNION` khác số cột/kiểu dữ liệu giữa 2 truy vấn | Bắt buộc số cột và kiểu dữ liệu tương ứng phải khớp |
| Nhầm `INNER JOIN` và `LEFT JOIN` làm mất dữ liệu | Cân nhắc kỹ loại JOIN cần dùng theo yêu cầu bài toán |

---
