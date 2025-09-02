#include <iostream>
#include <cmath>
#include <algorithm>
#include<cstdlib>
#include<winsock.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <cctype>
#include <bits/stdc++.h>
#define blockSize 4
// Macro to find the product of x ({02}) and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
// Macro to multiply numbers in the Galois Field(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

using namespace std;
int phi, p, q,n,d,e,g,f,p1,q1,e1,d1,shift,primaa[100], k=0,s=0;
string asdf,plaintext1, aes_abjad,abjad,ans;
string kunci1="";
char kunci[100];
int rounds = 0;
int keyLength = 0;
unsigned char plaintext[16], encrypted[16], state[4][4], hasildekrip[16];
unsigned char roundKey[240], Key[32];
// Fungsi untuk mencari nilai gcd (greatest common divisor) dari dua bilangan

void leftrotate(string &s, int d)
{
reverse(s.begin(), s.begin()+d);
reverse(s.begin()+d, s.end());
reverse(s.begin(), s.end());
}

void rightrotate(string &s, int d)
{
leftrotate(s, s.length()-d);
}

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Fungsi untuk mencari nilai modulo dengan menggunakan algoritma eksponensial cepat
int mod(int base, int exponent, int modulus)
{
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Fungsi untuk mencari nilai e yang cocok untuk kunci publik
int findE(int phi) {
    int e = 2;
    while (e < phi)
	{
        if (gcd(e, phi) == 1) return e;
        e++;
    }
    return 1;
}

// Fungsi untuk mencari nilai d yang cocok untuk kunci privat
int findD(int e, int phi) {
    int d = 1;
    while (d < phi) {
        if ((d * e) % phi == 1) return d;
        d++;
    }
    return 0;
}

// Fungsi untuk mengenkripsi pesan dengan menggunakan kunci publik
string encrypt(int e, int n, string ciphertext)
{
    string kunciRSA = "";
    for (char c : ciphertext) {
        int x = (int)c;
        int y = mod(x, e, n);
        kunciRSA += to_string(y) + " ";
    }
    return kunciRSA;
}

string encrypt1(int e, int n, string ciphertext)
{
    string kunciRSA1 = "";
    for (char c : ciphertext) {
        int x = (int)c;
        int y = mod(x, e, n);
        kunciRSA1 += to_string(y) + "";
    }
    return kunciRSA1;
}


string encryptRailFenceCipher(string enkripkunci, int k)
{
  // Buat matriks untuk menyimpan pesan yang akan dienkripsi
  char matrix[k][enkripkunci.length()];

  // Inisialisasi matriks dengan karakter spasi
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < enkripkunci.length(); j++) {
      matrix[i][j] = ' ';
    }
}

  // Isi matriks dengan karakter dari enkripkunci
  int direction = 1;
  int row = 0;
  for (int i = 0; i < enkripkunci.length(); i++) {
    matrix[row][i] = enkripkunci[i];

    // Ubah arah jika sudah mencapai ujung atas atau bawah matriks
    if (row == k - 1) {
      direction = -1;
    } else if (row == 0) {
      direction = 1;
    }

    // Geser ke baris berikutnya
    row += direction;
  }

  // Buat ciphertext dengan menggabungkan karakter di setiap baris
  string ciphertext = "";
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < enkripkunci.length(); j++) {
      if (matrix[i][j] != ' ') {
        ciphertext += matrix[i][j];
      }
    }
  }

  return ciphertext;
}

string caesar(string kunci, int k) {
    string enkripkunci="";

    for (char& ch : kunci) {
        //mengabaikan karakter selain huruf
        if (isalpha(ch)) {
            char base = isupper(ch)?'A':'a';
            ch = (ch-base+k)%26+base;
        }
        enkripkunci+=ch ;
    }

    return enkripkunci;
}

// Fungsi untuk mendekripsi pesan dengan menggunakan kunci privat

int enkripsi_kunci()
{
	int k;
	awal:
	cout<<"  ****************************************ENKRIPSI KUNCI*************************************"<<endl;
    // Nilai p dan q yang akan digunakan untuk menghasilkan kunci publik dan privat
	cout<<"\tMasukkan Plaintext Kunci                           :";
	cin.getline(kunci, 100);
    // Menghitung nilai n dan phi
    plaintext1=kunci;
    cout<<"\tMasukkan pergeseran  (Caesar Cipher)               :";
	cin>>k;
    string enkripkunci = caesar(kunci,k);
    // Pesan yang akan dienkripsi
    cout<<"\tPlaintext Caesar Cipher                            : " <<enkripkunci<<endl;
    // Iterasi melalui setiap karakter dalam string
    // Inisialisasi variabel untuk menghitung jumlah ASCII dan jumlah karakter
    int sum = 0;
    int count = 0;
    for (char c : enkripkunci)
    {
    // Tambahkan nilai ASCII karakter ke variabel sum
    sum += (int)c;
    count++;
    }
    // Hitung rata-rata ASCII dengan membagi sum dengan jumlah karakter
    double average = (double)sum / count;
    // Pembulatan rata-rata ASCII ke atas atau ke bawah
    int rounded_average;
    if (average - (int)average >= 0.5) {
    // Pembulatan ke atas
    rounded_average = (int)round(average);
    }
    else {// Pembulatan ke bawah
    rounded_average = (int)average;
    }
    // Cetak hasil
    cout << "\tRata-rata ASCII string yang dibulatkan adalah    : " << rounded_average << endl;
    int largestDigit = 0;
    while (rounded_average > 0)
	{
        int digit = rounded_average % 10;
        if (digit > largestDigit) {
            largestDigit = digit;
        }
        rounded_average /= 10;
    }
    cout << "\tAngka terbesar dari hasil rata-rata              : " << largestDigit << endl;
    string ciphertext = encryptRailFenceCipher(enkripkunci, largestDigit);
    cout<<"\tHasil Enkripsi Rail Fence                          : " <<ciphertext<<endl;
    //proses RSA
    int panjangkunci=ciphertext.length();
    for (int i = 0; i < panjangkunci; i++) {
    char c = ciphertext[i];
    // Mengkonversi huruf menjadi bilangan decimal ASCII
    int ascii = (int)c;
    // Mengecek apakah bilangan decimal ASCII tersebut merupakan bilangan prima atau bukan
    bool is_prime = true;
    if (ascii == 1 || ascii == 0){
        is_prime = false;
    }
    else {
      for (int j = 2; j <= sqrt(ascii); j++) {
        if (ascii % j == 0) {
          is_prime = false;
          break;
        }
      }
    }
    // Menampilkan
    if (is_prime)
    {
		std::cout << "\tASCII dari huruf '" << c << "' adalah " << ascii <<" (angka prima)";
		k=k+1;
		primaa[s]=ascii;
		s=s+1;
		if(k==2)
		{
			panjangkunci=2;
		}
    	std::cout<<std::endl;
    }
    else {
    	std::cout << "\tASCII dari huruf '" << c << "' adalah " << ascii <<" (bukan angka prima)";
    	std::cout<<std::endl;
	}
    }

    if (k < 2)
    {
	std::cout<<std::endl;
	std::cout<<"\tTidak cukup jumlah prima yang dibutuhkan, silahkan input ulang !"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"\ttekan apapun untuk melanjutkan!"<<std::endl;
	getch();
	goto awal;
    }
    std::cout<<std::endl;
    std::cout<<"\tDidapatkan 2 bilangan prima sebagai kunci yaitu : "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tBilangan Prima 1 			: "<<primaa[0]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tBilangan Prima 2 			: "<<primaa[1]<<std::endl;
    std::cout << std::endl;
    // Menghitung nilai n dan phi
     n = primaa[0] * primaa[1];
     phi = (primaa[0] - 1) * (primaa[1] - 1);
    // Mencari nilai e yang cocok untuk kunci publik
     e = findE(phi);
     d = findD(e,phi);
    std::cout<<"\tDidapatkan Kunci privat yaitu	            : "<<d<<std::endl;// Mencari nilai d yang cocok untuk kunci privat
    std::string kunciRSA = encrypt(e, n, ciphertext);
    std::string kunciRSA1 = encrypt1(e, n, ciphertext);
    cout << "\tKunci RSA                                    : "<<kunciRSA<<endl;
    cout << "\tHasil Kunci RSA                              : "<<kunciRSA1<<endl;


    for (char pecahan_hexa : kunciRSA1)
    {
    // Konversi digit ke dalam abjad
    if (pecahan_hexa >= '0' && pecahan_hexa <= '9') {
      abjad += (char)('a' + (pecahan_hexa - '0'));
    } else {
      abjad += (char)('A' + (pecahan_hexa - 'A'));
    }
  }
    std::cout << "\tKunci yang terbangun dalam bentuk string    : " << abjad << std::endl;
    return 0;
    cout<<"  *************************************************************"<<endl;
}

int get_SBox_Value(int num)
{
	// lookup table
	int sbox[256] =   {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
	};
	return sbox[num];
}

// Returns inverse Rijndael S-box value
int get_SBox_Inverse(int num)
{
	// lookup table
	int rsbox[256] =	{
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
	};

	return rsbox[num];
}

// Lookup Table for round constant word array
// Contains the values given by x to the power (i-1) being powers of x ({02}) in the field Galois Field (28)
int Rcon[255] =		{
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb	};

// Deduces round keys from the primary Key provided
void Expand_Keys()
{
	int i,j;
	unsigned char temp[4],k;

	// Use the primary Key for first round
	for(i = 0; i < keyLength; i++)
	{
		roundKey[i*4]=Key[i*4];
		roundKey[i*4+1]=Key[i*4+1];
		roundKey[i*4+2]=Key[i*4+2];
		roundKey[i*4+3]=Key[i*4+3];
	}

	// Each subsequent round key is deduced from previously deduced round keys
	while (i < (blockSize * (rounds+1)))
	{
					for(j=0;j<4;j++)
					{
						temp[j]=roundKey[(i-1) * 4 + j];
					}
					if (i % keyLength == 0)
					{
						// Rotate the bytes in a word to the left.
						{
							k = temp[0];
							temp[0] = temp[1];
							temp[1] = temp[2];
							temp[2] = temp[3];
							temp[3] = k;
						}

						// Take a four-byte input and apply the S-box to each of the four bytes
						{
							temp[0]=get_SBox_Value(temp[0]);
							temp[1]=get_SBox_Value(temp[1]);
							temp[2]=get_SBox_Value(temp[2]);
							temp[3]=get_SBox_Value(temp[3]);
						}

						temp[0] =  temp[0] ^ Rcon[i/keyLength];
					}
					else if (keyLength > 6 && i % keyLength == 4)
					{
						{
							temp[0]=get_SBox_Value(temp[0]);
							temp[1]=get_SBox_Value(temp[1]);
							temp[2]=get_SBox_Value(temp[2]);
							temp[3]=get_SBox_Value(temp[3]);
						}
					}
					roundKey[i*4+0] = roundKey[(i-keyLength)*4+0] ^ temp[0];
					roundKey[i*4+1] = roundKey[(i-keyLength)*4+1] ^ temp[1];
					roundKey[i*4+2] = roundKey[(i-keyLength)*4+2] ^ temp[2];
					roundKey[i*4+3] = roundKey[(i-keyLength)*4+3] ^ temp[3];
					i++;
	}
}

// Add round key to state by XOR-ing
void Add_Round_Key(int round)
{
	int i,j;
	for (i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			state[j][i] ^= roundKey[round * blockSize * 4 + i * blockSize + j];
		}
	}
}

// Substitute state matrix values with corresponding S-box values
void Sub_Bytes()
{
	int i,j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			state[i][j] = get_SBox_Value(state[i][j]);

		}
	}
}

// Same as Sub_Bytes, but uses reverse SBox
void Inv_Sub_Bytes()
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			state[i][j] = get_SBox_Inverse(state[i][j]);

		}
	}
}

// Shift the rows in the state to the left by the row number value
void Shift_Rows()
{
	unsigned char temp;

	// First row by 1
	temp=state[1][0];
	state[1][0]=state[1][1];
	state[1][1]=state[1][2];
	state[1][2]=state[1][3];
	state[1][3]=temp;

	// Second row by 2
	temp=state[2][0];
	state[2][0]=state[2][2];
	state[2][2]=temp;
	temp=state[2][1];
	state[2][1]=state[2][3];
	state[2][3]=temp;

	// Third row by 3
	temp=state[3][0];
	state[3][0]=state[3][3];
	state[3][3]=state[3][2];
	state[3][2]=state[3][1];
	state[3][1]=temp;
}

// Same as Shift_Rows, but shifts right instead
void Inv_Shift_Rows()
{
	unsigned char temp;

	temp = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;
	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	temp = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;
}

// Mixes the columns of the state matrix
void Mix_Columns()
{
	int i;
	unsigned char x1, x2, x3;
	for (i = 0; i < 4; i++)
	{
		x1 = state[0][i];
		x3 = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
		x2 = state[0][i] ^ state[1][i]; x2 = xtime(x2); state[0][i] ^= x2 ^ x3;
		x2 = state[1][i] ^ state[2][i]; x2 = xtime(x2); state[1][i] ^= x2 ^ x3;
		x2 = state[2][i] ^ state[3][i]; x2 = xtime(x2); state[2][i] ^= x2 ^ x3;
		x2 = state[3][i] ^ x1; x2 = xtime(x2); state[3][i] ^= x2 ^ x3;
	}
}

// Inverse mixing of columns
void Inv_Mix_Columns()
{
	int i;
	unsigned char x1, x2, x3, x4;
	for (i = 0; i < 4; i++)
	{
		x1 = state[0][i];
		x2 = state[1][i];
		x3 = state[2][i];
		x4 = state[3][i];

		state[0][i] = Multiply(x1, 0x0e) ^ Multiply(x2, 0x0b) ^ Multiply(x3, 0x0d) ^ Multiply(x4, 0x09);
		state[1][i] = Multiply(x1, 0x09) ^ Multiply(x2, 0x0e) ^ Multiply(x3, 0x0b) ^ Multiply(x4, 0x0d);
		state[2][i] = Multiply(x1, 0x0d) ^ Multiply(x2, 0x09) ^ Multiply(x3, 0x0e) ^ Multiply(x4, 0x0b);
		state[3][i] = Multiply(x1, 0x0b) ^ Multiply(x2, 0x0d) ^ Multiply(x3, 0x09) ^ Multiply(x4, 0x0e);
	}
}

void Encrypt()
{
	int i,j,round=0;

	// Copy plaintext to state array
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[j][i] = plaintext[i * 4 + j];
		}
	}

	// Add the first round key to the state before starting the rounds
	Add_Round_Key(0);

	// The first rounds-1 rounds are the same
	for (round = 1; round < rounds; round++)
	{
		Sub_Bytes();
		Shift_Rows();
		Mix_Columns();
		Add_Round_Key(round);
	}

	// Last round has no Mix_Columns()
	Sub_Bytes();
	Shift_Rows();
	Add_Round_Key(rounds);

	// Copy the state array to output
	for (i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			encrypted[i * 4 + j] = state[j][i];
		}
	}
}

void Decrypt()
{
	int i, j, round = 0;

	// Copy cyphertext to state array
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			state[j][i] = encrypted[i * 4 + j];
		}
	}

	Add_Round_Key(rounds);

	for (round = rounds - 1; round>0; round--)
	{
		Inv_Shift_Rows();
		Inv_Sub_Bytes();
		Add_Round_Key(round);
		Inv_Mix_Columns();
	}

	Inv_Shift_Rows();
	Inv_Sub_Bytes();
	Add_Round_Key(0);

	// Copy the state array to output
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			plaintext[i * 4 + j] = state[j][i];
		}
	}
}

string generateKey(int length) {
    string key;
    for (int i = 0; i < length; ++i) {
        key += rand() % 26 + 'A'; // Generate huruf kapital acak
    }
    return key;
}

class Vig {
   public:
      string kunci1;
   Vig(string kunci1) {
      for (int i = 0; i < kunci1.size(); ++i) {
         if (kunci1[i] >= 'A' && kunci1[i] <= 'Z')
            this->kunci1 += kunci1[i];
         else if (kunci1[i] >= 'a' && kunci1[i] <= 'z')
            this->kunci1 += kunci1[i] + 'A' - 'a';
      }
   }
   string encryption(string hexa) {
      string output;
      for (int i = 0, j = 0; i < hexa.length(); ++i) {
         char c = hexa[i];
         if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if (c < 'A' || c > 'Z')
            continue;
         output += (c + kunci1[j] - 2 * 'A') % 26 + 'A'; //added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
         j = (j + 1) % kunci1.length();
      }
      return output;
   }
   string decryption(string ciphertext) {
      string output;
      for (int i = 0, j = 0; i < ciphertext.length(); ++i) {
         char c = ciphertext[i];
         if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if (c < 'A' || c > 'Z')
            continue;
         output += (c - kunci1[j] + 26) % 26 + 'A';//added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
         j = (j + 1) % kunci1.length();
      }
      return output;
   }
};

string RC4(string ciphertext, string kunci1)
{
    // Inisialisasi variabel
    int S[256], T[256];
    for (int i = 0; i < 256; i++)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + kunci1[i % kunci1.length()]) % 256;
        swap(S[i], S[j]);
    }
    int i = 0, k = 0;
    string hasil_enkripsi = "";
    for (int n = 0; n < ciphertext.length(); n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        k = S[(S[i] + S[j]) % 256];
        hasil_enkripsi += char(k ^ ciphertext[n]);
    }
    return hasil_enkripsi;
}

int enkripsi_pesan()
{
	cout<<"  *********************************ENKRIPSI PESAN**********************"<<endl;
	string pesan, hexa, key, ciphertext,hexa2,cipher_vernam, pesan_enkripsi;
    int i,j,G;

    cout<< "\tMasukkan pesan                        : ";
    cin>>pesan;

    cout<<"\tMasukkan Kunci                         : ";
    cin>>kunci1;
	strcpy((char*)plaintext,ans.c_str());
	// Ask user for key length
	/// ROUNDS DAH PASTI 256

	// Calculate actual keyLength and rounds from the user input
	rounds=256;
	keyLength = rounds / 32;
	rounds = keyLength + 6;

	// Clear input buffer
	/// ada flush
	// Ask user for the plaintext to be encrypted in HEX
	int k,l;
	for( k = 0; k < pesan.size(); k++) {
        int character= int(pesan[k]); // converting each character to its ascii value
        cout<< hex;
        character; // basefield is now set to hex
        plaintext[k]=(unsigned char)character;
    }
    if(pesan.size()<blockSize*4){
        for(l=k;l<blockSize*4;l++)
        {
            plaintext[l]='0';
        }
    }
    cout<<"\tPlainteks Yang Akan Dienkripsi         : ";
        for(int m=0;m<blockSize*4;m++){
        cout<<plaintext[m];
    }

    	for(i = 0; i < kunci1.size(); i++) {
        int karakter_kunci= int(kunci1[i]); // converting each character to its ascii value
        cout<<hex;
        karakter_kunci; // basefield is now set to hex
        Key[i]=(unsigned char)karakter_kunci;
    }
    if(kunci1.size()<keyLength*4){
        for(j=i;j<keyLength*4;j++)
        {
            Key[j]='0';
        }
    }
	printf("\n\tKunci Rijndael: ");
    for(int p=0;p<keyLength*4;p++){
        cout<<Key[p];
    }
	// Ask user for the key in HEX
	// Expand_Keys before encryption
	Expand_Keys();
	Encrypt();

    char satuanhexa[4*blockSize*2+1];  // String yang akan menyimpan hasil konversi
    for (int k = 0; k < 4*blockSize; k++) {
        sprintf(satuanhexa+k*2, "%02X", encrypted[k]);  // Menyatukan byte hexa ke dalam string
    }
    char string[4*blockSize+1];  // String yang akan menyimpan hasil konversi
    for (int k = 0; k < 4*blockSize; k++) {
        sprintf(string+k, "%c", encrypted[k]);  // Menyatukan byte hexa ke dalam string
    }

    cout<<"\n\tHasil Enkripsi Rijndael          : "<<satuanhexa<<endl;
    hexa = satuanhexa ;

for (char pecahan_hexa : satuanhexa) {
    // Konversi digit ke dalam abjad
    if (pecahan_hexa >= '0' && pecahan_hexa <= '9') {
      aes_abjad += (char)('a' + (pecahan_hexa - '0'));
    }
    else {
      aes_abjad += (char)('A' + (pecahan_hexa - 'A'));
    }
  }
    Vig v(kunci1);
    ciphertext = v.encryption(hexa);
    cout << "\tHasil enkripsi vigenere: " << ciphertext << endl;
    j = kunci1.length();
        cout<<"\tMasukkan nilai G (maks 1-"<<j<<")     : " ;
        cin>>G;
        leftrotate(kunci1, G);
        cout<<"\tKunci Baru                : " <<kunci1;
        cout<<endl;
    pesan_enkripsi = RC4(ciphertext, kunci1);
    cout<<"\tHasil Enkripsi RC4             : " <<pesan_enkripsi<<endl;
    cout<<endl;
    cout<<"  ****************************************************************************"<<endl;


    return 0;
}

string RC4_decrypt(string cipher_otp, string kunci1)
{
    // Inisialisasi variabel
    int S[256], T[256];
    for (int i = 0; i < 256; i++)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + kunci1[i % kunci1.length()]) % 256;
        swap(S[i], S[j]);
    }
    int i = 0, k = 0;
    string hasil_dekripsi = "";
    for (int n = 0; n < cipher_otp.length(); n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        k = S[(S[i] + S[j]) % 256];
        hasil_dekripsi += char(k ^ cipher_otp[n]);
    }
    return hasil_dekripsi;
}

int dekripsi_pesan()
{
	rounds=256;
	keyLength = rounds / 32;
	rounds = keyLength + 6;
	dekrip:
	string message, kunci2,plain_rot13,cipher_otp,cipher_aes_hexa,plain_aes,ciphertext2;
	int i,j,k;
	cout<<" *************************DEKRIPSI PESAN**********************"<<endl;
	cout<<"\tMasukkan Cipherteks           : ";cin>>cipher_otp;
	cout<<"\tMasukkan Kunci                : ";cin.ignore();getline(cin,kunci1);
	j = kunci1.length();
        cout<<" Masukkan nilai k (maks 1-"<<j<<")     : " ;
        cin>>k;
        leftrotate(kunci1, k);
        cout<<"\tKunci Baru                : " <<kunci1;
        cout<<endl;
    string pesan_dekripsi = RC4_decrypt(cipher_otp, kunci1);
    cout<<"\tDekripsi RC4 (Plaintext Pesan) : "<<pesan_dekripsi<<endl;
    string kuncivige=pesan_dekripsi;
    int d = kunci1.size();
    int e=kuncivige.size();
    if(d>e)
    {
        d%=e;
    }
    leftrotate(kuncivige,d);
    cout << "\tHasil kunci vigenere berdasarkan plainteks: " << kuncivige << endl;
    Vig v(kuncivige);
    string ciphertext = v.encryption(pesan_dekripsi);
    cout << "\tHasil enkripsi vigenere: " << ciphertext << endl;
    char ascii[16];
    for (int i = 0; i < ciphertext.length(); i += 2) {
    sscanf(ciphertext.substr(i, 2).c_str(), "%hhx", &encrypted[i / 2]);
  }
  /*int j;
    if(kunci1.size()<keyLength*4){
        for(j=i;j<keyLength*4;j++)
        {
            Key[j]='0';
        }
    }
	printf("\n\tKunci Rijndael: ");
    for(int p=0;p<keyLength*4;p++){
        cout<<Key[p];
    }*/
cout<<"\tKunci Rijndael :";
cin>>kunci2;
  if(kunci2.length()!=32)
  {
  	cout<<"\tKunci yang diinput harus sama dengan 32"<<endl;getch();
  	system("cls");goto dekrip;
  }
  for(int i = 0; i < kunci2.size(); i++) {
        int karakter_kunci= int(kunci2[i]); // converting each character to its ascii value
        cout<<hex;
        karakter_kunci; // basefield is now set to hex
        Key[i]=(unsigned char)karakter_kunci;
    }

    Expand_Keys();
	Decrypt();
	printf("\n\tHasil Dekrip              : ");
	for (int i = 0; i < blockSize * 4; i++)
	{
		printf("%c", plaintext[i]);
	}
	printf("\n\n");

 cout<<"Klik Apa saja untuk kembali...";
 getch();
 return 0;

}

string decrypt(int d, int n, string kunciRSA)
{
	kunciRSA+=" ";
    string decryptedkunci = "";
    string number = "";
    for (char c : kunciRSA)
	{
        if (c == ' ') {
            int x = stoi(number);
            int y = mod(x, d, n);
            char z = (char)y;
            decryptedkunci += z;
            number = "";
        }
        else {
            number += c;
        }
    }
    return decryptedkunci;
}

// Fungsi untuk mendekripsi ciphertext menggunakan Rail Fence Cipher
string decryptRailFenceCipher(string decryptedkunci, int key) {
    // Buat matriks untuk menyimpan plaintext
    char matrix[key][decryptedkunci.length()];

    // Inisialisasi matriks dengan karakter spasi
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < decryptedkunci.length(); j++) {
            matrix[i][j] = ' ';
        }
    }

    // Isi matriks dengan ciphertext
    int row = 0, col = 0;
    bool down = true;
    for (int i = 0; i < decryptedkunci.length(); i++) {
        matrix[row][col] = '*';

        if (down) {
            row++;
            if (row == key) {
                row = key - 2;
                down = false;
            }
        } else {
            row--;
            if (row == -1) {
                row = 1;
                down = true;
            }
        }
        col++;
    }

    // Rekonstruksi plaintext dari matriks
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j <decryptedkunci.length(); j++) {
if (matrix[i][j] == '*') {
matrix[i][j] = decryptedkunci[index++];
}
}
}
// Buat string untuk menyimpan hasil dekripsi
string plaintext;
row = 0, col = 0;
down = true;
for (int i = 0; i < decryptedkunci.length(); i++) {
    plaintext += matrix[row][col];

    if (down) {
        row++;
        if (row == key) {
            row = key - 2;
            down = false;
        }
    } else {
        row--;
        if (row == -1) {
            row = 1;
            down = true;
        }
    }
    col++;
}

return plaintext;
}

string caesar1(string plaintext1, int key) {

        string kunciawal="";
    for (char& ch : plaintext1) {
        //mengabaikan karakter selain huruf
        if (isalpha(ch)) {
            char base = isupper(ch)?'A':'a';
            ch = (ch-base-key+26)%26+base;
        }
                kunciawal+=ch;
    }
    return kunciawal;
}

int dekripsi_kunci()
{
	int key;
	string kunciRSA;
	cout<<endl<<endl;
	awal:
	cout<<"  ****************************************DEKRIPSI KUNCI******************************************"<<endl;
	cout<<"\tMasukkan Cipherteks                                 : ";
	getline(cin,kunciRSA);
	int panjangkunci=kunciRSA.length();
    for (int i = 0; i < panjangkunci; i++)
    {
    char c = kunciRSA[i];
    // Mengkonversi huruf menjadi bilangan decimal ASCII
    int ascii = (int)c;
    // Mengecek apakah bilangan decimal ASCII tersebut merupakan bilangan prima atau bukan
    bool is_prime = true;
    if (ascii == 1 || ascii == 0){
        is_prime = false;
    }
    else {
      for (int j = 2; j <= sqrt(ascii); j++) {
        if (ascii % j == 0) {
          is_prime = false;
          break;
        }
      }
    }
    // Menampilkan
    if (is_prime)
    {
		std::cout << "\tASCII dari huruf '" << c << "' adalah " << ascii <<" (angka prima)";
		k=k+1;
		primaa[s]=ascii;
		s=s+1;
		if(k==2)
		{
			panjangkunci=2;
		}
    	std::cout<<std::endl;
    }
    else {
    	std::cout << "\tASCII dari huruf '" << c << "' adalah " << ascii <<" (bukan angka prima)";
    	std::cout<<std::endl;
	}
    }

    if (k < 2)
    {
	std::cout<<std::endl;
	std::cout<<"\tTidak cukup jumlah prima yang dibutuhkan, silahkan input ulang !"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"\ttekan apapun untuk melanjutkan!"<<std::endl;
	getch();
	goto awal;
    }
    std::cout<<std::endl;
    std::cout<<"\tDidapatkan 2 bilangan prima sebagai kunci yaitu   : "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tBilangan Prima 1 			: "<<primaa[0]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tBilangan Prima 2 			: "<<primaa[1]<<std::endl;
    std::cout << std::endl;
    // Menghitung nilai n dan phi
     n = primaa[0] * primaa[1];
     phi = (primaa[0] - 1) * (primaa[1] - 1);
    // Mencari nilai e yang cocok untuk kunci publik
     e = findE(phi);
     d = findD(e,phi);
    std::cout<<"\tDidapatkan Kunci privat yaitu	                    : "<<d<<std::endl;// Mencari nilai d yang cocok untuk kunci privat
    string decryptedkunci = decrypt(d, n, kunciRSA);
    cout <<"\tHasil Dekripsi RSA      : " << decryptedkunci << endl;

    // Iterasi melalui setiap karakter dalam string
    // Inisialisasi variabel untuk menghitung jumlah ASCII dan jumlah karakter
    int sum = 0;
    int count = 0;
    for (char c : decryptedkunci)
    {// Tambahkan nilai ASCII karakter ke variabel sum
    sum += (int)c;
    count++;
    }

    // Hitung rata-rata ASCII dengan membagi sum dengan jumlah karakter
    double average = (double)sum / count;
    // Pembulatan rata-rata ASCII ke atas atau ke bawah
    int rounded_average;
    if (average - (int)average >= 0.5)
    {
    // Pembulatan ke atas
    rounded_average = (int)round(average);
    }
    else
    {
    // Pembulatan ke bawah
    rounded_average = (int)average;
    }
    // Cetak hasil
    cout << "\tRata-rata ASCII string yang dibulatkan adalah    : " << rounded_average << endl;
    int largestDigit = 0;
    while (rounded_average > 0)
	{
        int digit = rounded_average % 10;
        if (digit > largestDigit) {
            largestDigit = digit;
        }
        rounded_average /= 10;
    }
    cout << "\tAngka terbesar dari hasil rata-rata              : " << largestDigit << endl;
    string plaintext1 = decryptRailFenceCipher(decryptedkunci, largestDigit);
    cout<<"\tKunci Rail Fence Cipher                            : " <<plaintext1<<endl;
    cout<<"\tMasukkan Pergeseran  (Caesar Cipher)               : ";
    cin>>key;
	string kunciawal = caesar1(plaintext1,key);
    cout <<"\tPlaintext Awal (Caesar Cipher)                    : " << kunciawal << endl;
    getch();
    exit(0);
    cout<<"  ************************************************************************************************"<<endl;
}

int selesai()
{
	 cout<<"  ************************************************************************************************"<<endl;
     cout<<"                                                  SELESAI                                         "<<endl;
     cout<<"  ************************************************************************************************"<<endl;
}

int main(int argc, char *argv[])
{
int jawab;
menu:
    system("cls");
     cout<<"  *******************************************************************************************************************"<<endl;
     cout<<"               Program Algoritma Caesar Cipher + Rail Fence Ciphher + RSA Dan AES + RC4 + Vigenere Cipher           "<<endl;
     cout<<"  *******************************************************************************************************************"<<endl;
     cout<<"\t1.) Enkripsi Kunci\n";
     cout<<"\t2.) Enkripsi Pesan\n";
     cout<<"\t3.) Dekripsi Pesan\n";
     cout<<"\t4.) Dekripsi Kunci\n";
     cout<<"\t5.) Selesai\n";
     cout<<"\tSilahkan memilih menu sesuai nomor... "<<endl;
     cout<<"\tPilihan Anda :";
	 cin>>jawab;
     cin.ignore(); // mengabaikan input spasi yang terjadi ketika input jawab tadi
     system("cls");
	switch(jawab)
	{
    case 1:
	{
		enkripsi_kunci();
		getch();
        system("cls");
        goto menu;
	}
    case 2:
    {
        enkripsi_pesan();
        getch();
        system("cls");
        goto menu;
	}
    case 3:
    {
        dekripsi_pesan();
        getch();
        system("cls");
        goto menu;
	}
    case 4:
    {
        dekripsi_kunci();
        getch();
        system("cls");
        goto menu;
	}
	case 5:
	{
		selesai();
        getch();
        system("cls");
        goto menu;
		}
	default:
        cout<<"\tPilihan Anda salah, silahkan coba kembali";
        system("cls");
        goto menu;
}
}


