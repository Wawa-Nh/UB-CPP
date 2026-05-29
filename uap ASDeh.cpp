#include <iostream>
using namespace std;

#define JUMLAH_WILAYAH 4

string kodeWilayah[JUMLAH_WILAYAH] = {"010", "011", "012", "028"};

//isi dari tipe data sensor
struct DataSensor{
	float temperature;
	float humidity;
	int airQuality;
	bool smoke;
	float noise;
};

//isi dari node linkedlist
struct User{
	string userID;
	string nama;
	DataSensor sensor;
	float monitoringScore;
	int wilayahKe;
	User *pNext;
};

//Head LinkedList
//dideklarasi secara global, agar bisa diakses semua fungsi 
User *pHead = nullptr;

/*
=== Fungsi hitungMonitoring ===
berfungsi untuk menghitung monitoring score
*/
float hitungMonitoring(DataSensor s){
	float jumlahScore = 0;
	
	if (s.temperature >= 20 && s.temperature <= 27)
		jumlahScore++;
	if (s.humidity >= 40 && s.humidity <= 60)
		jumlahScore++;
	if (s.airQuality >= 0 && s.airQuality <= 50)
		jumlahScore++;
	if (s.smoke == false)
		jumlahScore++;
	if (s.noise >= 30 && s.noise <= 55)
		jumlahScore++;
	
	return jumlahScore / 5 * 100;
}

/*
=== Fungsi cekID === 
berfungsi untuk mengetahui ada duplikat atau gaa
*/
bool cekID(string id){
	User *temp = pHead;
	
	while (temp != NULL){
		if (temp->userID == id)
			return true;
			
		temp = temp->pNext;
	}
	return false;
}

//Tugas 2 Mencari User
void cariUser(string ID){
    User *temp = pHead;
    if (temp == NULL){
		cout<< "list kosong\n";
	}
    while (temp != NULL){ //jika temp tidak sama dengan null = tidak ada list
		//jika user = user dicari
        if (temp->userID == ID){
            cout<< "User ditemukan\n";
            cout<< "User ID :" << temp->userID << "\n";
            cout<< "Nama Pelanggan :" << temp->nama << "\n";
            cout<< "Monitoring Score :" << (int)temp->monitoringScore << "%\n";
            cout<< "Temperature : " << temp->sensor.temperature << "\n";
            cout<< "Humidity : " << temp->sensor.humidity << "\n";
            cout<< "Air Quality : " << temp->sensor.airQuality << "\n";
            cout<< "Smoke : " << temp->sensor.smoke << "\n";
            cout<< "Noise : " << temp->sensor.noise << "\n";
            return;
        }
		//Lanjut ke list selanjutnya
        temp = temp->pNext; 
    }
	//jika user tidak ada di list
    cout<< "User tidak ditemukan\n";
}


//Tugas 3 Mencari id
void updateID(string ID){
	User *temp = pHead;
	
	while (temp){
		if (temp->userID == ID){
			cout<<"User ID ditemukan! Lakukan pembaharuan sebagai berikut:\n";
			cout<<"UserID: "<<temp->userID;
			cout<<"\nNama User Baru: ";
			cin>>temp->nama;
			
			cout << "Nilai Temperatur Baru (-10 s/d 50 C): ";
			while(true){
				cin >> temp->sensor.temperature;
				if (temp->sensor.temperature < -10 || temp->sensor.temperature > 50){
					cout << "Data yang Dimasukkan Tidak Valid, Ulangi input data: \n" << endl;
				}else break;
			}
			
			cout << "Nilai Humidity baru (0 s/d 100 %) : ";
			while(true){
				cin >> temp->sensor.humidity;
				if (temp->sensor.humidity < 0 || temp->sensor.humidity > 100){
					cout << "Data yang Dimasukkan Tidak Valid, Ulangi input data: \n" << endl;
				}else break;	
			}
			
			cout << "Nilai Air Quality baru (0 s/d 500) : ";
			while(true){
				cin >> temp->sensor.airQuality;	
				if (temp->sensor.airQuality < 0 || temp->sensor.airQuality > 500){
					cout << "Data yang Dimasukkan Tidak Valid, Ulangi input data: \n" << endl;
				}else break;	
			}
			
			int inputAsap;
			cout << "Nilai Smoke (0/1) : ";
			while(true){			
				cin >> inputAsap;
				if (inputAsap != 0 && inputAsap != 1) {
				cout << "Input Salah, Ulangi input data: \n" << endl;
				}else break;
			}
			temp->sensor.smoke = (inputAsap == 1);
			
			cout << "Nilai Noise Baru (0 s/d 120 dB) : ";
			while(true){
				cin >> temp->sensor.noise;
				if (temp->sensor.noise < 0 || temp->sensor.noise > 120){
					cout << "Input Salah, Ulangi input data: \n" << endl;
				}else break;
			}
			
			temp->monitoringScore = hitungMonitoring(temp->sensor);
			
			cout<<"Monitoring Score Baru: "<<temp->monitoringScore<<"%\n";
			
			cout << "\n=================================" << endl;
			cout << "       BERHASIL UPDATE USER!" << endl;
			cout << "=================================" << endl;
			cout << "User ID : " << temp->userID << endl;
			cout << "Nama : " << temp->nama << endl;
			cout << "Monitoring Score Baru: " << (int) temp->monitoringScore << "%" << endl;
			cout << "=================================" << endl;
			
			return;
		}
		temp = temp->pNext;
	}
	cout<<"User ID tidak ditemukan!";
	return;
}

//Kapital
//void kapital()

/*Tugas 1
=== Fungsi tambahUser === 
berfungsi untuk menambah data user
*/
void tambahUser(){
	cout << "\n====== TAMBAH USER ======\n";
	
	string id;
	cout << "Masukkan ID User : ";
	cin >> id;
	
	bool valid = false;
	int wilayah = -1;
	
	// cek 3 digit pertama
	for (int i = 0; i < JUMLAH_WILAYAH; i++){
		if (id.substr(0,3) == kodeWilayah[i]){
			valid = true;
			wilayah = i;
			break;
		}
	}
	
	//kalo 3 digit pertama tidak sesuai dengan wilayah
	if (valid == false){
		cout << "Kode wilayah tidak ditemukan!" << endl;
		return;
	}
	
	if (id.length() < 4){
		cout << "ID terlalu pendek!" << endl;
		return;
	}
	if (cekID(id)){
		cout << "ID sudah dipakai!" << endl;
		return;
	}
	
	cout << "\n====== MASUKKAN DATA USER ======\n";

	cout << "ID User : " << id << endl;
	string nama;
	cout << "Nama : ";
	cin.ignore();
	getline(cin, nama);
	
	// ------ Data Sensor ------
	DataSensor s;
	
	cout << "Temperatur (-10 s/d 50 C): ";
	cin >> s.temperature;
	if (s.temperature < -10 || s.temperature > 50){
		cout << "Data yang Dimasukkan Tidak Valid" << endl;
		return;
	}
	
	cout << "Humidity (0 s/d 100 %) : ";
	cin >> s.humidity;
	if (s.humidity < 0 || s.humidity > 100){
		cout << "Data yang Dimasukkan Tidak Valid" << endl;
		return;
	}
	
	cout << "Air Quality (0 s/d 500) : ";
	cin >> s.airQuality;	
	if (s.airQuality < 0 || s.airQuality > 500){
		cout << "Data yang Dimasukkan Tidak Valid" << endl;
		return;
	}
	
	int inputAsap;
	cout << "Smoke (0/1) : ";
	cin >> inputAsap;
	
	if (inputAsap != 0 && inputAsap != 1) {
		cout << "Input Salah" << endl;
		return;
	}
	s.smoke = (inputAsap == 1);
	
	cout << "Noise (0 s/d 120 dB) : ";
	cin >> s.noise;
	if (s.noise < 0 || s.noise > 120){
		cout << "Input Salah" << endl;
		return;
	}
	
	// ----- Hitung Score -----
	float nilai = hitungMonitoring(s);
	User *baru = new User;
	baru->userID = id;
	baru->nama = nama;
	baru->sensor = s;
	baru->monitoringScore = nilai;
	baru->wilayahKe = wilayah;
	baru->pNext = NULL;
	
	// ------ Linked List -----
	if (pHead == NULL){
		pHead = baru;
	}
	
	else{
		User *temp = pHead;
		
		while (temp->pNext != NULL){
			temp = temp->pNext;
		}
		temp->pNext = baru;
	}
	
	cout << "\n=================================" << endl;
	cout << "       BERHASIL TAMBAH USER!" << endl;
	cout << "=================================" << endl;
	cout << "User ID : " << id << endl;
	cout << "Nama : " << nama << endl;
	cout << "Monitoring Score : " << (int) nilai << "%" << endl;
	cout << "=================================" << endl;
}

//Tugas 4
void DeleteUser(){
	string jawaban = "iya";
	while(jawaban == "iya"){
		
		string input;
		cout<<"Cara menghapus: Ketik 'Hapus' diikuti ID user Contoh: Hapus 010111"<<endl;
		
        getline(cin, input);
        if(input.empty()){
        	getline(cin, input);
		}
        
        // Cek apakah input dimulai dengan "Hapus"
        if(input.substr(0,5) == "Hapus"){
            string kode = input.substr(6, input.length() - 6); // Ambil ID setelah spasi
			
			User* sekarang = pHead;
			User* sebelumnya = nullptr;
			bool ditemukan = false;
			
			if(sekarang == nullptr){
				cout<<"\nBelum ada id yang ditambah"<<endl;
				cout<<"silahkan tambahkan id dulu"<<endl;
				return;
				
			}else{
			while(sekarang != nullptr){
				if(sekarang->userID == kode ){
					User* hapus = sekarang;
					
					if(sebelumnya == nullptr){
						pHead = sekarang->pNext;
						sekarang = pHead;
					}
					else{
						sebelumnya->pNext = sekarang->pNext;
						sekarang = sekarang->pNext;
						
					}
					cout << "\n=================================" << endl;
		            cout << "      BERHASIL HAPUS USER!" << endl;
		            cout << "=================================" << endl;
					cout << "Menghapus: " << hapus->userID << " - " << hapus->nama << endl;
		            cout << "=================================" << endl;			
		            delete hapus;
		            ditemukan = true ;
		            break;
				}else{
					sebelumnya = sekarang;
					sekarang = sekarang->pNext;
				}
			}
			if(ditemukan){
		        cout << "\nUser dengan id " << kode <<" berhasil dihapus dari sistem "<< endl;
		    } else {
		        cout << "\nUser not found"<< endl;
		    }
		    cout<<"Hapus user id lagi?(iya/tidak) : ";
		    cin>>jawaban;
			}
		}
		else{
			cout <<"\nFormat salah! Gunakan: Hapus <ID>" << endl;
			cout<<"Hapus user id lagi?(iya/tidak) : ";
		    cin>>jawaban;
		}
	}
}

// Helper tugas 5;
void hitungSensor(int* temp, int* humidity, int* air, int* smoke, int* noise){
	User *t2 = pHead;
	while(t2){
		if (t2->sensor.temperature >= 20 && t2->sensor.temperature<= 27)
			(*temp)++;
		if (t2->sensor.humidity >= 40 && t2->sensor.humidity <= 60)
			(*humidity)++;
		if (t2->sensor.airQuality >= 0 && t2->sensor.airQuality <= 50)
			(*air)++;
		if (t2->sensor.smoke == false)
			(*smoke)++;
		if (t2->sensor.noise >= 30 && t2->sensor.noise <= 55)
			(*noise)++;
		
		t2 = t2->pNext;
	}
}

// Tugas 5
void printUser(){
	int jumlahlist = 0, ideal = 0;
	float average;
	User *temp = pHead;
	while (temp){
		jumlahlist++;
		temp = temp->pNext;
	}
	
	User *printArray[jumlahlist];
	temp = pHead;
	
	for (int i = 0; i < jumlahlist; i++){
		printArray[i] = temp;
		if(temp->monitoringScore == 100.0) ideal++;
		average += temp->monitoringScore;
		temp = temp->pNext;
	}
	average /= jumlahlist;
	
	bool swap = false;
	for (int i = 0; i < jumlahlist; i++){
		swap = false;
		for (int j = 0; j < jumlahlist - i; j++){
			if (printArray[j]->monitoringScore < printArray[j+1]->monitoringScore){
				swap = true;
				temp = printArray[j+1];
				printArray[j+1] = printArray[j];
				printArray[j] = temp;
			}
		}
		if (swap == false) break;
	}
	
	cout<<"\n\n===========================================================";
	cout<<"\nLAPORAN MONITORING IOT";
	cout<<"\n===========================================================";
	cout<<"\n Statistik Monitoring";
	cout<<"\n Jumlah User Dengan Pembacaan Ideal\t\t: "<<ideal;
	cout<<"\n Jumlah User Dengan Pembacaan Tidak Ideal\t: "<<jumlahlist-ideal;
	cout<<"\n Total Pelanggan\t\t\t\t: "<<jumlahlist;
	cout<<"\n Rata-rata Score\t\t\t\t: "<<average<<"%";
	
	cout<<"\n===========================================================";
	cout<<"\nRekap Sensor";
	
	int totalT = 0, totalH = 0, totalA = 0, totalS = 0, totalN = 0;
	hitungSensor(&totalT, &totalH, &totalA, &totalS, &totalN);
	
	cout<<"\nTemperature\t: "<<totalT<<" rumah";
	cout<<"\nHumidity\t: "<<totalH<<" rumah";
	cout<<"\nAir Quality\t: "<<totalA<<" rumah";
	cout<<"\nSmoke\t\t: "<<totalS<<" rumah";
	cout<<"\nNoise\t\t: "<<totalN<<" rumah";
	
	cout<<"\n===========================================================";
	for (int i = 0; i < jumlahlist; i++){
		cout<<"\nPeringkat "<<i+1;
		cout<<"\nUser ID\t\t\t: "<<printArray[i]->userID;
		cout<<"\nNama Pelanggan\t\t: "<<printArray[i]->nama;
		cout<<"\nMonitoring Score\t: "<<printArray[i]->monitoringScore<<"%";
		cout<<"\nWilayah\t\t\t: "<<printArray[i]->wilayahKe;
		cout<<"\nData Sensor ";	
		cout<<"\n*Temp\t\t\t: "<<printArray[i]->sensor.temperature<<"C";
		cout<<"\n*Humidity\t\t: "<<printArray[i]->sensor.humidity<<"%";
		cout<<"\n*Air Quality\t\t: "<<printArray[i]->sensor.airQuality;
		cout<<"\n*Smoke\t\t\t: "<<(printArray[i]->sensor.smoke? "1": "0");
		cout<<"\n*Noise\t\t\t: "<<printArray[i]->sensor.noise<<" dB";
		cout<<"\n===========================================================";
	}
	cout<<"\n";
}

int main(){
	int pilihan;
	string tambah;
	do{
    	cout << "\n=================================" << endl;
        cout << "     PILIIHAN UTAMA PROGRAM" << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah User" << endl;
        cout << "2. Cari User" << endl;
        cout << "3. Update User" << endl;
        cout << "4. Hapus User" << endl;
        cout << "5. Print User" << endl;
        cout << "6. Keluar" << endl;
        cout << "=================================" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
		
		switch(pilihan){
			case 1:	{									//Tugas 1

				do{tambahUser();
					cout << "\nTambah User lagi? (iya / tidak) : ";
					cin >> tambah;
				}
				while (tambah == "iya");
			
				cout << "\n\n=========== DATA USER ===========\n";
				User *temp= pHead;
				int no = 1;
				while (temp != NULL){
					cout << no++ << ". ";
					
					cout << temp->userID << " | " << temp->nama << " | Score : " << (int)temp->monitoringScore << "%" << endl;
					temp = temp->pNext;
				}break;}
			
			case 2:{										//Tugas 2
	
			    cout<< "\n\n=========== CARI USER ===========\n";
			    string perintahCari;
			    string lanjutCari = "iya";
			    do{
			        cout << "masukkan kode user yang ingin dicari\n";
			        cin >> perintahCari; 
			        // Cek apakah kata pertama yang diketik adalah "Cari"
			        if (perintahCari == "Cari"){
			            string idDicari;
			            cin>> idDicari; // Mengambil ID yang di masukkan
			            cariUser(idDicari);
			        } else {
			            break; // Jika bukan kata "Cari"diawal, maka berhenti
			        }
					//apakah ingin mencari lagi?
			        cout << "\nCari user lagi? (iya / tidak) : ";
			        cin >> lanjutCari;
			    } while (lanjutCari == "iya");
			    break;}
		
		
			case 3:	{										//Tugas 3
				
				cout<<"\n\n=========== UPDATE USER ===========\n";
				string updater;
				tambah = "iya";
				do {
					cout<<"Update user dengan cara menuliskan Update diikuti dengan User ID (cth: Update 01022102)\nLewati bagian ini dengan menulis apapun selain format tersebut\n\n";
					cin.ignore();
					getline(cin,updater);
					if (updater.substr(0,6) == "Update"){
						updateID(updater.substr(7, updater.length()-7));
					}else{
						break;
					}
					cout<<"\n Update user lagi? (iya / tidak) : ";
					cin>>tambah;
				}while (tambah == "iya");
				break;}
			
			case 4: {											//Tugas 4
			
				cout<<"\n\n=========== DELETE USER ===========\n";
				DeleteUser();
				break;
			}
			
			case 5: { 											//Tugas 5
				cout<<"\n\n=========== PRINT USER ===========\n";
				printUser();
				break;
			}
				
			case 6:{
				cout << "\nTerima kasih kakak telah menggunakan program ini" << endl;
				cout<<"============== GOODBYEEEE ============="<<endl;
				break;
			}
				
			default:{
                cout << "\nPilihan tidak valid! Silakan pilih 1-6." << endl;
                break;
    		}
        }
        
        if(pilihan != 6){
            cout << "\nsilahkan pilih lagi di menu..";
        }
        
    } while(pilihan != 6);
			
			


	return 0;
}
