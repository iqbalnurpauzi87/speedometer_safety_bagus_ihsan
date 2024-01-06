input:
magnet  -Rpm     	-by arduino
gyro	-kemiringan 	-esp32
gps	-lokas   	-by arduino

output:
oled			-esp32
buzzer			-esp32
relay			-esp32
telegram		-esp32


troble terakhir
pin serial di esp32 kurang

18/12/2023
pembacaan kecepatan pakai gps error 2-5 km/h di bawah 40
pembacaan pakai magnet bisa di jadiin hiasan saja
telegram dan kemiringan dan oled sudah oke

20/12
tinggal kirim lokasi gps di esp ke telegram, komanya belum bisa kekirim
test led harusnya simple
speedometer, gps, kemiringan, telegram sudah oke
