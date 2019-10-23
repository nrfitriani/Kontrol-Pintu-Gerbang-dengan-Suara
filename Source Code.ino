String state;
char c = 0;
int LS1 = 11;//limit switch
int LS2 = 12;// limit switch
int M1 = 7;// tes poin
int M2 = 8;// tes poin
int IL1 = 10;// led indicator1
int IL2= 9;// led indicator2
int IN_1 = 4;
int IN_2 = 3;
int EN_A = 6;
boolean LSState = 0;//nilai awal limit sw 
String cmd=""; // data serial dikirim satu persatu maka harus dikumpulkan dalam bentuk "string"
bool sread = false;//membersihkan data pembacaan serial

void setup() {
  Serial.begin(9600);
  while (!Serial) {}//menyiapkan serial 
  Serial.println("Goodnight moon!");// serial siap

  pinMode (LS1, INPUT_PULLUP);
  pinMode (LS2, INPUT_PULLUP);
  pinMode (IN_1, OUTPUT);
  pinMode (IN_2, OUTPUT);
  pinMode (EN_A, OUTPUT);
  pinMode (IL1, OUTPUT);
  pinMode (IL2, OUTPUT);
  pinMode (M1, OUTPUT);
  pinMode (M2, OUTPUT);
}

void loop() { 
  if(Serial.available()>0){ // saat data serial tersedia
    char c = Serial.read();// serial read akan membaca data yang dikirim per karakter 
    switch(c){
      case '<' : cmd = ""; break;// saat "<" dikirim cmd/perintah di kosongkan 
      case '>' : sread = true; break; // saat ">" diterima. data serial bernilai benar
      default  : cmd += c;
      }
    }

  if(sread){//jika data serial bernilai true maka ;
    control();//masuk ke void control
    sread=false; //setelah void control selesai di eksekusi data serial yg tadi sudah di proses tidak berlaku lagi dan kembali ke awal void loop
    }
}


void control(){
    bool keys = true; // mengunci kondisi atau perintah
    while(keys){//saat "kunci" lakukan ini
        LSState = digitalRead (LS1) && digitalRead (LS2); //keadaan limit sw
        if(LSState == LOW){berhenti();cmd="";keys = false;}//jika limit sw ditekan maka motor berhenti, perintah dikosongkan dan kunci dibuka(siap menerima data baru)
        if (cmd == "open"){buka();}//perintah yg mungkin terjadi
        else if (cmd == "close") {tutup();} //perintah yg mungkin terjadi
        }
        
    Serial.print(cmd);//serial menampilkan dan memroses perintah baru
  }

void berhenti(){//motor berhenti
analogWrite (EN_A,0);
digitalWrite(IN_1,LOW);
digitalWrite (IN_2,LOW);
digitalWrite (M1, LOW);
digitalWrite (M2, LOW);
digitalWrite(13, LOW);
}

void tutup(){//tutup gerbang
analogWrite (EN_A,120);
digitalWrite(IN_1,LOW);
digitalWrite (IN_2,HIGH);
digitalWrite (M1, LOW);// tes poin untuk motor 1
digitalWrite (M2, HIGH);// tes poin motor 2
digitalWrite (IL2, HIGH);// led 2 nyala pintu tertutup
}

void buka(){//buka gerbang
analogWrite (EN_A,120);
digitalWrite(IN_1,HIGH);
digitalWrite (IN_2,LOW);
digitalWrite (M1, HIGH);
digitalWrite (M2, LOW);
digitalWrite (IL1, HIGH);//led 1 nyala pintu terbuka  
}
