# 前提
- STM32L431CCT6の開発ボード(Platypus5384が自作)
- CR2032電池(RTCのバックアップ用)
- デジットのVFDキット(https://eleshop.jp/shop/g/g96I412/)
- 電源電圧は18~24V

### 思ったことメモ
- 水晶は30ppm、1日3秒くらいズレる　　
  - 温度補償品(通常温度で~3.5ppm)にしたい。3日で1秒?? 
- 6桁ダイナミック点灯したら24Vがちょうどいい 18Vはちょっと暗い
  -1桁なら18Vでも明るい
- ヒーター?用の分圧抵抗めっちゃ熱い、24Vで触れない

- 
# STM32L431CCT6の開発ボード外観と回路図
![image](https://github.com/platypus5384/VFD-test/assets/51383611/2320c063-fbb8-4f82-a300-708711cc50c0)
![image](https://github.com/platypus5384/VFD-test/assets/51383611/8ebb6e1f-24b9-4a42-adeb-1914c4dbd6fc)


# ピンアウト
![image](https://github.com/platypus5384/VFD-test/assets/51383611/04760ecb-178b-4f4f-80f0-231b047586b1)


# 完成写真
![image](https://github.com/platypus5384/VFD-test/assets/51383611/684cdac4-c7d3-431a-b740-fc3a795c9978)
