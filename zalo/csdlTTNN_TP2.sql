--xoa cac thuc the neu co san truoc
drop table monhoc;
drop table diem;
drop table phieuthu;
drop table lop;
drop table hocvien;
drop table loailop;
drop table chuongtrinh;
drop table khoahoc;

----------------------

create table KHOAHOC (
   MAKH                 char(4)              not null,
   TENKH                NVARCHAR2(50)           not null,
   NGAYBD               date            not null,
   NGAYKT               date            not null ,
   constraint PK_KHOAHOC primary key  (MAKH),
   constraint CK_KHOAHOC  CHECK (NGAYKT>NGAYBD)
);


create table CHUONGTRINH (
   MACT                 char(5)              PRIMARY KEY,
   TENCT                NVARCHAR2(100)          not null
);

create table LOAILOP (
   MALOAI               char(5)              not null  primary key,
   MACT                 char(5)              not null,
   TENLOAI              NVARCHAR2(100)          not null,
   constraint FK_LOAILOP FOREIGN  key  (MACT) REFERENCES CHUONGTRINH(MACT)
);

create table LOP (
   MALOP                char(4)              not null PRIMARY KEY,
   MALOAI               char(5)              not null,
   TENLOP               NVARCHAR2(50)          not null,
   SISO                 smallint             not null CHECK (SISO>12),
   MAKH   char(4)              not null,
   constraint FK1_LOP FOREIGN  key  (MALOAI) REFERENCES LOAILOP(MALOAI),
   constraint FK2_LOP FOREIGN  key  (MAKH) REFERENCES KHOAHOC(MAKH)
   
);

create table HOCVIEN (
   MAHV                 char(6)				primary key,
   TENHV                NVARCHAR2(40)          not null,
   GIOITINH             smallint                  not null,
   NGAYSINH             date            not null,
   SDT                  char(10)                  not null,
   DIACHI               NVARCHAR2(100)         not null
);

create table PHIEUTHU (
   SOPT                 CHAR(8)               PRIMARY KEY,
   MAHV                char(6)               not null,
   MALOP                char(4)              not null,
   NGAYLAPPHIEU         date	            not null,
   THANHTIEN        NUMERIC NOT NULL,
   constraint FK1_PT FOREIGN  key  (MAHV) REFERENCES HOCVIEN(MAHV),
   constraint FK2_PT FOREIGN  key  (MALOP) REFERENCES LOP(MALOP)
);

create table MONHOC (
   MAMH                 char(4)             PRIMARY KEY,
   TENMH                NVARCHAR2(30)          not null
);



create table DIEM (
   MAMH                 char(4)              not null,
   MAHV                 char(6)                 not null,
   MALOP                char(4)              not null,
   DIEM                 float            not null CHECK(DIEM>=0),
   constraint PK_DIEM primary key  (MAMH, MAHV, MALOP),
   constraint FK1_DIEM FOREIGN  key  (MAHV) REFERENCES HOCVIEN(MAHV),
   constraint FK2_DIEM FOREIGN  key  (MALOP) REFERENCES LOP(MALOP),
   constraint FK3_DIEM FOREIGN  key  (MAMH) REFERENCES MONHOC(MAMH)
);


INSERT INTO KHOAHOC VALUES('K001',N'Khóa 1','2020-01-10','2020-03-20');
INSERT INTO KHOAHOC VALUES('K002',N'Khóa 2','2020-02-28','2020-05-28');
INSERT INTO KHOAHOC VALUES('K003',N'Khóa 3','2020-04-10','2020-07-20');
INSERT INTO KHOAHOC VALUES('K004',N'Khóa 4','2020-06-15','2020-09-20');


INSERT INTO CHUONGTRINH VALUES('CT001',N'Tiếng Anh Tổng Quát');
INSERT INTO CHUONGTRINH VALUES('CT002',N'Tiếng Anh Trẻ Em');
INSERT INTO CHUONGTRINH VALUES('CT003',N'Tiếng Anh Luyện Kỹ Năng');
INSERT INTO CHUONGTRINH VALUES('CT004',N'Chương Trình TOEIC');
INSERT INTO CHUONGTRINH VALUES('CT005',N'Tiếng Anh IELTS');
INSERT INTO CHUONGTRINH VALUES('CT006',N'Chương Trình CamBridge');
INSERT INTO CHUONGTRINH VALUES('CT007',N'Chứng Chỉ Tiếng Anh 6 Bậc(A1,B1,B2,C1)');



INSERT INTO LOAILOP VALUES('LL001','CT001',N'Tiếng Anh căn bản');
INSERT INTO LOAILOP VALUES('LL002','CT001',N'Tiếng Anh A1');
INSERT INTO LOAILOP VALUES('LL003','CT001',N'Tiếng Anh A2');
INSERT INTO LOAILOP VALUES('LL004','CT001',N'Tiếng Anh B1');
INSERT INTO LOAILOP VALUES('LL005','CT001',N'Tiếng Anh B2');
INSERT INTO LOAILOP VALUES('LL006','CT001',N'Tiếng Anh C1');
INSERT INTO LOAILOP VALUES('LL007','CT001',N'Tiếng Anh C2');
INSERT INTO LOAILOP VALUES('LL008','CT001',N'Tiếng Anh nâng cao');
--
INSERT INTO LOAILOP VALUES('LL009','CT002',N'Anh văn nhi đồng');
INSERT INTO LOAILOP VALUES('LL010','CT002',N'Anh văn thiếu nhi');
INSERT INTO LOAILOP VALUES('LL011','CT002',N'Anh văn thiếu niên');
INSERT INTO LOAILOP VALUES('LL012','CT002',N'Tiếng Anh tổng quát dành cho thiếu niên(B1)');
INSERT INTO LOAILOP VALUES('LL013','CT002',N'Tiếng Anh tổng quát dành cho thiếu niên(B1+)');
INSERT INTO LOAILOP VALUES('LL014','CT002',N'Tiếng Anh nâng cao');
INSERT INTO LOAILOP VALUES('LL015','CT002',N'IELTS');
--

INSERT INTO LOP VALUES ('L001','LL001',N'Lớp 1','30','K001');
INSERT INTO LOP VALUES ('L002','LL001',N'Lớp 2','30','K001');
INSERT INTO LOP VALUES ('L003','LL002',N'Lớp 1','25','K001');





INSERT INTO HOCVIEN VALUES('HV0001',N'Đỗ Bình An',1,'2000-11-02','0917217036','Cờ Đỏ - Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0002',N'Đỗ Gia Bảo',1,'2001-12-02','0917217036','Ôn Môn- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0003',N'Đỗ Phúc Vinh',1,'2002-11-02','0917217036','Cù Lao Dung - Sóc Trăng');
INSERT INTO HOCVIEN VALUES('HV0004',N'Thạch Chí Tâm',1,'2000-01-02','0917217036','Châu Thành- An Giang');


INSERT INTO HOCVIEN VALUES('HV0005',N'Lê Cẩm Giao','0',to_date('2000-11-05','yyyy-mm-dd'),'0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0006',N'Huỳnh Gia Bảo','1',to_date('2000-11-02','yyyy-mm-dd'),'0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0007',N'Đỗ An Nhiên','0',to_date('2001-01-02','yyyy-mm-dd'),'0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0008',N'Trần Hoàng Uyên Anh',0,'2002-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0009',N'Trấn Thành',1,'1998-07-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0010',N'Trịnh Giai Nhân',1,'2000-11-02','0917217036','Châu Thành- An Giang');
INSERT INTO HOCVIEN VALUES('HV0011',N'Lê Thanh Hoàng',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0014',N'Lê Thanh Tâm',1,'2002-01-17','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0015',N'Huỳnh Ngọc Minh',1,'2007-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0016',N'Ngũ Hoàng Gia Bảo',1,'2005-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0017',N'Trịnh Ngọc Gia Bảo',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0018',N'Bùi Bảo Ngọc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0019',N'Lê Ngọc Kim Khánh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0020',N'Lê Huỳnh My',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0021',N'Trần Ngọc Tuyết',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0022',N'Trần Ngọc Khánh Minh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0023',N'Trần Ngọc Minh Anh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0024',N'Trần Lê Kim Ngân',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0025',N'Lê Thanh Trân',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0026',N'Lê Thanh Tâm',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0027',N'Trần Ngọc Tuyền',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0028',N'Trần Huỳnh Gia Nhi',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0029',N'Trần Lê Kim Thoa',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0030',N'Bùi Mộng Cầm',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0031',N'Trần Mộng Điệp',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0032',N'Trần Kim Quyên',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0033',N'Trần Lê Anh Thư',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0034',N'Trần Thanh Nghi',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0035',N'Trần Bùi Tố Nga',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0036',N'Trần Thị Kim Cúc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0037',N'Trần Bảo Thy',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0038',N'Nguyễn Thị Bảo Nghi',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0039',N'Lê Thanh Ngọc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0040',N'Trần Thị Như Ý',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0041',N'Trần Ngọc Mỹ Ý',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0042',N'Trần Ngọc Phúc An',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0043',N'Trần Ngọc Minh Anh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0044',N'Trần Ngọc Phúc An',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0047',N'Trần Ngọc Bích',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0048',N'Trần Thanh Nhân',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0049',N'Đỗ Tố Uyên',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0050',N'Lê Hà My',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0051',N'Lê Ngọc Trân',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0052',N'Nguyễn Minh Thi',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0053',N'Trần Ngọc Anh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0054',N'Trần Ngọc Khánh Như',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0055',N'Trần Ngọc Tiên',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0056',N'Trần Kiều Tiên',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0057',N'Trần Hữu Phước',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0058',N'Trần Hoàng Khang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0059',N'Trần Lâm Trường',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0060',N'Trần Trọng Phúc',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');

INSERT INTO HOCVIEN VALUES('HV0061',N'Trần Trọng Nghĩa',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0062',N'Trần Minh Nhựt',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0063',N'Lê Thanh An',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0064',N'Lê Kim Thy',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0065',N'Trần Huyền Trang',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0066',N'Trần Minh Thư',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0067',N'Trần Thanh Ngân',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0068',N'Nguyễn Quốc Kiệt',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0069',N'Lâm Thị Như',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0070',N'Lâm Minh Thư',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0071',N'Đỗ Ngọc Như',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0072',N'Trần Trọng Phúc',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0073',N'Nguyễn Thanh Như',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0074',N'Lư Huyền Trang',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
--
INSERT INTO HOCVIEN VALUES('HV0075',N'Lư Anh Thư',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0076',N'Đỗ Hà My',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0077',N'Đỗ Minh Khang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0078',N'Đỗ Hoàng Khang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0079',N'Đỗ Gia Khang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0080',N'Đỗ Bùi Minh Anh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0081',N'Lê Tuấn Anh',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0082',N'Đỗ Diễm Ly',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0083',N'Đỗ Tường Vy',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0084',N'Đỗ Ngọc Chúc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0085',N'Đỗ Minh Nhựt',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0086',N'Đỗ Minh Hoàng',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0087',N'Đỗ Minh Trung',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0088',N'Đỗ Minh Long',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0089',N'Võ Văn Khánh Quốc',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0090',N'Nguyễn Trung Hậu',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0091',N'Đỗ Lam Nhã',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0092',N'Huỳnh Minh Sơn',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0093',N'Hà Duy Mạnh',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0094',N'Lưu Hà Phước',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0095',N'Đỗ Ngọc Kiều Oanh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0096',N'Đỗ Gia Minh',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0097',N'Đỗ Thanh Nhi',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0098',N'Lê Tấn Đạt',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0099',N'Lê Kim Ánh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0100',N'Đỗ Phương Thùy',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0101',N'Lâm Thị Thảo Linh',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0102',N'Đỗ Thanh Thảo',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0103',N'Đỗ Ngọc Thùy',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0104',N'Đỗ Ngọc Phương',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0105',N'Đỗ Thạch Anh',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0106',N'Lư Tấn Anh',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0107',N'Đỗ Hà Giang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');

INSERT INTO HOCVIEN VALUES('HV0108',N'Đỗ Trường Giang',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0109',N'Đỗ Hà My',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0110',N'Đỗ Tuấn Phát',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0111',N'Đỗ Tuấn Kiệt',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
---
INSERT INTO HOCVIEN VALUES('HV0112',N'Đỗ Hà Huy',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0113',N'Đỗ Hà Ngọc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0114',N'Đỗ Thị Cẩm Giang',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0115',N'Lê Bảo Trang',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0116',N'Lê Kiều My',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0117',N'Phạm Thanh Trúc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0118',N'Phạm Ngọc Hà',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0119',N'Trương Thanh Ngọc',0,'2000-11-02','0917217036','Phong Điền- Cần Thơ');
INSERT INTO HOCVIEN VALUES('HV0120',N'Đỗ Phạm Gia Huy',1,'2000-11-02','0917217036','Phong Điền- Cần Thơ');










insert into PHIEUTHU values('PT000002','HV0002','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000003','HV0003','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000004','HV0004','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000005','HV0005','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000006','HV0006','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000007','HV0007','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000008','HV0008','L001','2021-06-01',1350000);
insert into PHIEUTHU values('PT000009','HV0009','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000010','HV0010','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000011','HV0011','L001','2021-06-02',1350000);
-- insert into PHIEUTHU values('PT000012','HV0012','L001','2021-06-02',1350000);
-- insert into PHIEUTHU values('PT000013','HV0013','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000014','HV0014','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000015','HV0015','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000016','HV0016','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000017','HV0017','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000018','HV0018','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000019','HV0019','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000020','HV0020','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000021','HV0021','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000022','HV0022','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000023','HV0023','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000024','HV0024','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000025','HV0025','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000026','HV0026','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000027','HV0027','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000028','HV0028','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000029','HV0029','L001','2021-06-02',1350000);
insert into PHIEUTHU values('PT000030','HV0030','L001','2021-06-02',1350000);

insert into PHIEUTHU values('PT000031','HV0031','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000032','HV0032','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000033','HV0033','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000034','HV0034','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000035','HV0035','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000036','HV0036','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000037','HV0037','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000038','HV0038','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000039','HV0039','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000040','HV0040','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000041','HV0041','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000042','HV0042','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000043','HV0043','L003','2021-06-02',1450000);
insert into PHIEUTHU values('PT000044','HV0108','L003','2021-06-05',1450000);
insert into PHIEUTHU values('PT000045','HV0109','L003','2021-06-05',1450000);
insert into PHIEUTHU values('PT000046','HV0110','L003','2021-06-05',1450000);
insert into PHIEUTHU values('PT000047','HV0111','L003','2021-06-05',1450000);
insert into PHIEUTHU values('PT000070','HV0044','L003','2021-06-05',1450000);





INSERT INTO MONHOC(MAMH,TENMH) VALUES ('MH01',N'Nghe');
INSERT INTO MONHOC(MAMH,TENMH) VALUES ('MH02',N'Nói');
INSERT INTO MONHOC(MAMH,TENMH) VALUES ('MH03',N'Đọc');
INSERT INTO MONHOC(MAMH,TENMH) VALUES ('MH04',N'Viết');


INSERT INTO DIEM values  ('MH01','HV0002', 'L001', 5.5);
INSERT INTO DIEM values  ('MH02','HV0002', 'L001', 6.5);
INSERT INTO DIEM values  ('MH03','HV0002', 'L001', 8.5);
INSERT INTO DIEM values  ('MH04','HV0002', 'L001', 3.5);

INSERT INTO DIEM values  ('MH01','HV0003', 'L001', 5.25);
INSERT INTO DIEM values  ('MH02','HV0003', 'L001', 6.8);
INSERT INTO DIEM values  ('MH03','HV0003', 'L001', 7.5);
INSERT INTO DIEM values  ('MH04','HV0003', 'L001', 5.5);

INSERT INTO DIEM values  ('MH01','HV0004', 'L001', 7.5);
INSERT INTO DIEM values  ('MH02','HV0004', 'L001', 6.5);
INSERT INTO DIEM values  ('MH03','HV0004', 'L001', 7.5);
INSERT INTO DIEM values  ('MH04','HV0004', 'L001', 5.0);

INSERT INTO DIEM values  ('MH01','HV0005', 'L001', 7.5);
INSERT INTO DIEM values  ('MH02','HV0005', 'L001', 8.0);
INSERT INTO DIEM values  ('MH03','HV0005', 'L001', 8.0);
INSERT INTO DIEM values  ('MH04','HV0005', 'L001', 7.75);

INSERT INTO DIEM values  ('MH01','HV0006', 'L001', 5.5);
INSERT INTO DIEM values  ('MH02','HV0006', 'L001', 6.5);
INSERT INTO DIEM values  ('MH03','HV0006', 'L001', 4.5);
INSERT INTO DIEM values  ('MH04','HV0006', 'L001', 3.5);

