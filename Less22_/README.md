# Bài 14: Autosar Classic

## Tổng quan

__AUTOSAR__ (AUTomotive Open System ARchitecture) là một tiêu chuẩn toàn cầu cho phát triển phần mềm ô tô với mục tiêu là chuẩn hóa kiến trúc phần mềm cho các hệ thống điều khiển điện tử (ECU) trong ô tô, nhằm tăng tính khả chuyển, khả mở rộng và giảm chi phí phát triển.

| **❌ Không sử dụng AUTOSAR**  | **✅ Có sử dụng AUTOSAR**  |
|:----------------------------|-------------------------|
|  Thiếu sự đồng nhất giữa các task của ECU.  |  Có sẵn các tiêu chuẩn để dựa vào.  |
|  Khả năng tái sử dụng thấp.  |  Khả năng tái sử dụng phần mềm cao với các dự án khác nhau.  |
|  Quản lý lỗi và bảo trì phức tạp.  |  Dễ dàng thay đổi để tương thích với các dòng MCU khác nhau.  |
| Hệ thống thiếu linh hoạt, mở rộng và phát triển hệ thống khó khăn.  |  Phần mềm và phần mềm được tách biệt với nhau.  |
|  Làm việc nhóm khó khăn.  |  Dễ quản lý và bảo trì phần mềm.  |

## Kiến trúc Autosar Classic 

Sử dụng kiến trúc phân tầng để phân tách phần mềm ứng dụng độc lập với phần cứng khỏi các phần mềm phụ thuộc phần cứng.  

Ở mức cao nhất, kiến trúc AUTOSAR chia thành __ba lớp chính__ chạy trên vi điều khiển:
- __Lớp Ứng Dụng (Application Layer)__: chứa các phần mềm ứng dụng chức năng (theo dạng __Software Components – SWC__). Đây là nơi hiện thực các chức năng điều khiển/giám sát cụ thể của xe (ví dụ: điều khiển động cơ, phanh, chiếu sáng...).
- __Môi Trường Thực Thi (Runtime Environment - RTE)__: lớp trung gian (middleware) nằm giữa Application và BSW, đóng vai trò như một “__ảo hóa giao tiếp__” – kết nối các thành phần phần mềm với nhau và với lớp cơ bản, độc lập với việc chúng nằm trên cùng một ECU hay khác ECU. RTE hiện thực khái niệm Virtual Functional Bus (VFB) – một bus ảo giúp các SWC giao tiếp với nhau mà không cần biết chi tiết hạ tầng bên dưới​
- __Lớp Phần Mềm Cơ Bản (Basic Software - BSW)__: Lớp phần mềm cơ bản nằm dưới RTE, bao gồm các __thành phần gần với phần cứng__ như hệ điều hành, trình điều khiển, dịch vụ hệ thống, ngăn xếp giao tiếp, v.v. Lớp BSW được chia thành các nhóm lớp con như __Service layer, ECU Abstraction layer, Microcontroller Abstraction layer__, và các __Complex Drivers__ đặc biệt.



## Tương Tác giữa các Lớp 

__Các lớp trên tương tác với nhau như sau:__
 - __Phần mềm ứng dụng (SWC)__ chỉ gọi các __interface__ được cung cấp bởi RTE thay vì gọi trực tiếp xuống phần cứng. Mọi trao đổi dữ liệu giữa các SWC, hoặc giữa SWC với dịch vụ/driver của BSW, đều thông qua RTE – tức là thông qua các __cổng giao tiếp ảo của VFB__.
- RTE sẽ __ánh xạ__ các kết nối ảo này thành kết nối thực tế: nếu hai SWC nằm trên cùng ECU, RTE sẽ gọi hàm trực tiếp nội bộ; nếu chúng nằm trên ECU khác nhau, RTE sẽ chuyển tiếp thông điệp qua giao thức mạng (CAN, LIN, v.v.) tương ứng
- Nhờ đó, __SWC không cần biết chúng chạy ở ECU nào__, việc phân bố chức năng lên các ECU có thể thay đổi linh hoạt mà không đòi hỏi sửa mã ứng dụng​

## Application Layer

__Application Layer__ là lớp trên cùng, chứa các __Software Component (SWC)__.  

- Mỗi SWC được xem như một đơn vị phần mềm __độc lập về phần cứng__, chỉ giao tiếp với bên ngoài thông qua các __cổng (ports)__ được xác định rõ.  

- Kiến trúc AUTOSAR định nghĩa tiêu chuẩn cho các __interface__ gắn với cổng, giúp cho SWC có thể tương tác với SWC khác hoặc với dịch vụ BSW mà __không cần quan tâm__ chúng nằm ở đâu.

- Bên trong mỗi SWC, logic hoạt động được chia thành các __runnable__ – là những đơn vị mã nhỏ nhất (thường tương ứng với một hàm C) thực hiện một tác vụ cụ thể của SWC​.Mỗi SWC có thể có một hoặc nhiều runnable tùy độ phức tạp.  

- Các runnable này không tự chạy liên tục mà được RTE __kích hoạt theo sự kiện hoặc theo lịch__: (__ví dụ__) RTE gọi `runnable` theo chu kỳ thời gian (định kỳ mỗi 10ms) hoặc khi có dữ liệu mới đến qua một cổng (event-based)​.  


AUTOSAR quy định các loại __sự kiện RTE__ để kích hoạt `runnables`, bao gồm sự kiện thời gian, sự kiện nhận dữ liệu (data receive), sự kiện gọi dịch vụ, sự kiện thay đổi chế độ,... Nhờ đó, việc lập lịch và đồng bộ giữa các thành phần được chuẩn hóa.

__=>__ Application Layer của AUTOSAR Classic cho phép các nhà phát triển định nghĩa rõ ràng các __thành phần phần mềm (SWC)__ cùng các __giao diện__ và __hành vi__ của chúng, nhưng __ẩn đi__ các __chi tiết cụ thể về phần cứng__ và truyền thông. Điều này tạo thuận lợi lớn cho việc tái sử dụng và phân chia công việc (mỗi SWC có thể do một nhóm hoặc nhà cung cấp khác nhau phát triển, miễn là tuân theo interface chuẩn).

## Runtime Environment (RTE)

__Runtime Environment (RTE)__ là lớp trung gian đặc biệt trong AUTOSAR, nó là “__đường truyền ảo__” kết nối tất cả các thành phần phần mềm.   

- Vai trò chính của RTE là __cung cấp hạ tầng giao tiếp__ cho các SWC ở Application Layer và giữa Application với Basic Software, đảm bảo rằng mỗi tương tác đều đúng theo cấu hình đã định.  

- RTE __đóng gói toàn bộ sự phức tạp của việc trao đổi dữ liệu__: từ việc gọi hàm, truyền thông tin giữa các luồng trên cùng ECU, cho đến gửi thông điệp qua bus mạng giữa các ECU – tất cả đều được thực hiện trong suốt đối với SWC.

Đối với `SWC`, `RTE` cung cấp các __interface hàm__ tương ứng với mỗi port của SWC. Khi SWC muốn gửi dữ liệu hay gọi dịch vụ, thay vì gọi trực tiếp SWC khác, nó gọi hàm do RTE cung cấp (__ví dụ: Rte_Write_PortName_SignalName(data) hoặc Rte_Call_ServerName_Operation(params)__). RTE đảm bảo lời gọi đó được chuyển đến đúng đối tượng: nếu là send/receive trong cùng ECU thì chép vào bộ đệm và kích hoạt runnable nhận; nếu là client/server trên cùng ECU thì gọi thẳng hàm server; nếu khác ECU thì đóng gói thành message để gửi qua bus. Ngược lại, khi có dữ liệu đến từ bus hoặc từ driver, RTE sẽ gọi hàm callback tương ứng để thông báo cho SWC.

`RTE` làm cho các `SWC` __tưởng như được kết nối qua một bus chung__ bất kể chúng thật sự nằm ở đâu. Điều này hỗ trợ mạnh mẽ tính linh hoạt và tái sử dụng: cùng một SWC có thể chạy trên ECU khác chỉ bằng cách cấu hình lại (RTE mới sẽ lo việc kết nối), không cần sửa mã SWC​.  

__=>__ RTE giúp __đảm bảo tính độc lập phần cứng của ứng dụng__, đồng thời chuẩn hóa phương thức giao tiếp và tương tác giữa các thành phần. Nhờ RTE, các nhà phát triển ứng dụng có thể lập trình SWC một cách tập trung vào chức năng, còn các chi tiết triển khai truyền thông, đồng bộ sẽ do RTE tự động đảm nhiệm dựa trên cấu hình đã thiết kế.

## Basic Software (BSW)

__Basic Software (BSW)__ là lớp phần mềm cơ bản nằm dưới RTE, cung cấp các dịch vụ cần thiết để chạy được các ứng dụng nhưng __không trực tiếp thực hiện chức năng nghiệp vụ__ nào của hệ thống.

`BSW` tương đương một __nền tảng phần mềm nhúng chuẩn__, bao gồm từ __hệ điều hành, giao tiếp mạng, quản lý bộ nhớ cho đến các driver truy cập phần cứng vi điều khiển__. AUTOSAR chia BSW thành các phân lớp (layer) logic để dễ quản lý và chuẩn hóa, bao gồm:

- __Microcontroller Abstraction Layer (MCAL)__: Lớp trừu tượng vi điều khiển. Đây là lớp thấp nhất của BSW, chứa các __device driver__ tương tác trực tiếp với các __peripheral__ của vi điều khiển (và các thiết bị ngoại vi được ánh xạ vào bộ nhớ vi điều khiển). __MCAL__ làm nhiệm vụ __che giấu sự khác biệt phần cứng__ của vi điều khiển, cung cấp các API chuẩn để tầng trên sử dụng. __Ví dụ__: các driver điều khiển __ADC, PWM, GPIO (DIO__), truyền thông __CAN, LIN, Ethernet, bộ nhớ Flash, EEPROM, Watchdog__, ... thuộc MCAL. Mỗi dòng vi điều khiển cụ thể sẽ có bộ MCAL riêng do nhà cung cấp vi điều khiển hoặc bên thứ ba phát triển phù hợp với AUTOSAR. Khi chuyển sang vi điều khiển khác, chỉ cần thay MCAL tương ứng mà không cần sửa các tầng trên.

- __ECU Abstraction Layer__: Lớp trừu tượng ECU. Lớp này nằm trên MCAL, cung cấp cách truy xuất thống nhất tới các thiết bị __cả bên trong lẫn bên ngoài__ vi điều khiển. ECU Abstraction đảm bảo rằng tầng trên __không cần biết thiết bị đó nằm trên chip hay ngoài chip__ – mọi truy cập đều qua giao diện chung. __Ví dụ__: thay vì gọi trực tiếp ADC driver, tầng trên có thể gọi thông qua __IO Hardware Abstraction__; thay vì truy cập thẳng một cảm biến ngoại vi qua SPI, có thể gọi qua __Sensor Interface__ trong __ECU abstraction__. Lớp này bao gồm các mô-đun interface như giao diện truyền thông (CAN Interface, LIN Interface), giao diện I/O, giao diện bộ nhớ… cung cấp các dịch vụ trừu tượng cho tầng trên sử dụng.

- __Services Layer (System Services__: Lớp dịch vụ hệ thống. Đây là lớp trên cùng của `BSW`, cung cấp các __dịch vụ chung__ cho ứng dụng và các thành phần khác sử dụng. Bao gồm: __Hệ điều hành__ (OS), dịch vụ quản lý thời gian và lịch trình, __dịch vụ truyền thông__ (COM stack như CAN NM, PDU Router, Signal gateway), __dịch vụ chẩn đoán__ (Diagnostic Event Manager, Fault Memory), __dịch vụ quản lý bộ nhớ__ (NVRAM Manager, Memory Stack), __dịch vụ mã hóa & bảo mật__ (Crypto Service). Chẳng hạn, AUTOSAR tích hợp một hệ điều hành thời gian thực (theo chuẩn OSEK/VDX) trong services layer để quản lý task và tài nguyên. Lớp dịch vụ này chính là nơi cung cấp các API như khởi tạo ECU, quản lý chế độ ECU (ECU State Manager), điều khiển chế độ ngủ/thức,... Các SWC ứng dụng có thể sử dụng những dịch vụ này (thông qua RTE) khi cần những chức năng hệ thống chung.

- __Complex Drivers (CDD – Complex Device Drivers)__: Đây không hẳn là một layer riêng mà là __các mô đun đặc biệt__ cho phép __truy cập trực tiếp phần cứng__, bỏ qua sự phân tầng chuẩn khi cần hiệu năng cao hoặc khi tích hợp các phần mềm/hardware legacy. Complex Drivers thường được dùng trong trường hợp __một chức năng đòi hỏi thời gian thực rất chặt chẽ__ hoặc __không phù hợp để chia nhỏ theo layer AUTOSAR__. __Ví dụ:__ điều khiển phun nhiên liệu hoặc đánh lửa có thể yêu cầu thời gian phản hồi cực nhanh, có thể được viết như một Complex Driver truy cập thẳng tới thanh ghi vi điều khiển, đồng thời cung cấp interface cho ứng dụng (như một SWC đặc biệt)​.Complex Drivers được phép gọi các chức năng của bất kỳ lớp BSW nào nếu cần (không bắt buộc qua RTE), nhưng vẫn có thể được ứng dụng gọi thông qua một interface chuẩn. AUTOSAR cho phép sử dụng CDD để tăng tính linh hoạt, nhưng khuyến cáo chỉ dùng khi thật cần thiết do nó phá vỡ một phần tính chuẩn hóa của mô hình layered.

__Phân lớp BSW trong AUTOSAR:__

| **Phân lớp BSW**  | **Chức năng chính**    | **Ví dụ module**      |
|-------------------------------------|----------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Microcontroller Abstraction (MCAL)** | Truy cập __trực tiếp phần cứng vi điều khiển__, cung cấp API trừu tượng cho peripherals.                                            | `Adc Driver`, `Can Driver`, `Dio (GPIO) Driver`, `Spi Driver`, `Watchdog Driver`|
| **ECU Abstraction**                 | Trừu tượng hóa thiết bị trong/ngoài vi điều khiển; cung cấp interface chung cho tầng trên sử dụng.                               | `CAN Interface (CanIf)`, `SPI Handler/Abstraction`, `Sensor Drivers Interface`, `MemoryInterface`|
| **Service Layer (System Services)** | Cung cấp __dịch vụ hệ thống và API chung__ cho ứng dụng và BSW. | `Operating System (OS)`, `Communication Services (COM, PDU Router)`, `Diagnostic Services (DEM/DCM)`, `NVRAM Manager`  |
| **Complex Drivers (CDD)**        | Module đặc biệt cho phép __truy cập thẳng hardware__ khi cần hiệu năng cao hoặc chức năng đặc thù không phù hợp phân lớp chuẩn.     | `IgnitionControl CDD`, `InjectionControl CDD (driver điều khiển đánh lửa/phun nhiên liệu trực tiếp)`, `Custom Sensor Driver` …  |

__=> Basic Software__ là nền tảng phần mềm chung, tiêu chuẩn hóa và ẩn mọi sự khác biệt của phần cứng bên dưới, cung cấp các dịch vụ cần thiết để các ứng dụng AUTOSAR có thể chạy một cách độc lập phần cứng. Các module BSW tuân thủ chuẩn AUTOSAR đảm bảo rằng khi __thay đổi vi điều khiển hoặc thiết bị ngoại vi__, ta chỉ cần thay đổi hoặc cấu hình lại BSW (thường do nhà cung cấp BSW thực hiện) mà không phải thiết kế lại ứng dụng. Đây chính là sức mạnh của việc __phân tách ứng dụng và nền tảng mà__ AUTOSAR mang lại.

## Mô hình dự án Autosar Classic 

# Hệ thống ECU điều khiển động cơ

File doc: https://docs.google.com/document/d/1-B0fCs_ma1bY3qy_J6m1z9HCNVuM4LwvwI_YXCCBtxU/edit?tab=t.0#heading=h.l12usgc0m52c  
Code demo: https://github.com/HalaAcademy/Autosar-Classic/tree/main/ECU_Engine_Control_Project/RTE  

Để hiểu rõ cách áp dụng AUTOSAR Classic trong thực tế, phần này trình bày mô hình cấu trúc của một dự án phần mềm ECU điều khiển động cơ ô tô tuân theo kiến trúc AUTOSAR.

__Cấu trúc thư mục:__
```
ECU_Engine_Control_Project/
│
├── BSW/                                  # Basic Software Layer
│   ├── ECU_Abstraction/                  # Abstraction Layer cho phần cứng
│   │   ├── IoHwAb_LoadSensor.h           # Driver cho cảm biến tải
│   │   ├── IoHwAb_MotorDriver.h         # Driver cho động cơ
│   │   ├── IoHwAb_SpeedSensor.h         # Driver cho cảm biến tốc độ
│   │   ├── IoHwAb_ThrottleSensor.h      # Driver cho cảm biến bàn đạp ga
│   │   ├── IoHwAb_TorqueSensor.h        # Driver cho cảm biến mô-men xoắn
│   │   └── ...                           # Các driver khác cho các cảm biến và phần cứng
│   ├── MCAL/                             # Microcontroller Abstraction Layer (MCAL)
│   │   ├── Adc.c                         # Driver ADC
│   │   ├── Can.c                         # Driver CAN
│   │   ├── Dio.c                         # Driver GPIO
│   │   ├── Pwm.c                         # Driver PWM
│   │   └── ...                           # Các driver khác
│   └── Services/                         # Các dịch vụ hệ thống
│       ├── Dem.c                         # Dịch vụ chẩn đoán
│       ├── Pdu_Router.c                  # Dịch vụ định tuyến PDU
│       └── ...                           # Các dịch vụ khác
│
├── RTE/                                  # Runtime Environment (RTE)
│   ├── Rte_TorqueControl.c               # Mã nguồn RTE cho TorqueControl SWC
│   └── Rte_TorqueControl.h               # Header cho RTE TorqueControl SWC
│
├── SWC/                                  # Software Components (SWC)
│   ├── Torque_Control.c                  # Mã nguồn cho SWC điều khiển mô-men xoắn
│   └── Torque_Control.h                  # Header cho SWC điều khiển mô-men xoắn
│
├── bin/                                  # Các file thực thi và đã biên dịch
│   ├── Main.c                            # Mã nguồn chính
│   ├── Makefile                          # File Makefile
│   ├── tool.exe                          # Công cụ hỗ trợ
│   └── tool.c                            # Mã nguồn cho công cụ hỗ trợ
│
└── ...
```



