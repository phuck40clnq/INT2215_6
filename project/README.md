            Game Project - SDL2

    - Phân công & phần tự làm

+ Phần tự làm:
Toàn bộ logic game, xử lý va chạm, tạo và quản lý item.  
Xây dựng hệ thống nâng cấp đạn, kỹ năng (buff, debuff)  
Thiết kế và xử lý va chạm giữa đạn và enemy  
Hệ thống điểm số, level, exp, pause/resume  
Tạo toàn bộ animation cho enemy và player  
Giao diện menu, thanh trạng thái, bảng điểm  
Hệ thống âm thanh (nhạc nền, hiệu ứng, on/off)  

+ Phần tham khảo:
Một số cấu trúc lớp được tham khảo từ code mẫu của môn học.  
Một số hình ảnh và font được lấy từ các nguồn miễn phí trên mạng theo đề xuất của ChatGPT, đảm bảo không vi phạm bản quyền. Không sử dụng tài nguyên trả phí.

---

    Tính năng đã làm theo checklist

✅ Dùng lệnh vẽ hình: SDL_RenderCopy, SDL_Rect  
✅ Hiển thị Texture: nhân vật, enemy, vật phẩm  
✅ Background  
✅ Event bàn phím: điều khiển nhân vật  
✅ Event chuột: menu, nút tạm dừng  
✅ Xử lý va chạm: giữa player, enemy, item, đạn  
✅ Score: tăng điểm khi tiêu diệt enemy  
✅ Sound on/off  
✅ Background music: nhạc nền trong game  
✅ Font: dùng TTF_RenderText cho giao diện  
✅ Menu: start game, hướng dẫn, thoát  
✅ Pause/Resume: nút bấm & phím P  
✅ Status bar: Level, Exp, Thời gian  
✅ Hiểu rõ code: tự viết/tự debug toàn bộ logic  
✅ Code rõ ràng, dễ đọc: chia file, comment logic  

❌ Animation: chưa có hoạt hình rõ ràng cho enemy chết hoặc đạn (chưa triển khai)  
❌ Lưu bảng điểm: chưa có chức năng lưu vào file  
