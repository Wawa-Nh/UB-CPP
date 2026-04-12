#include <iostream>
#include <string>
using namespace std;

class OrderNode{
	public:
		string nama;
		int urutanPembelian;
		OrderNode* next;
		OrderNode* prev;
		
		OrderNode(string nama, int urutan){
			this->nama = nama;
			urutanPembelian = urutan;
			next = prev = nullptr;
		}
};

class HDLL{
	public:
		OrderNode* head;
		OrderNode* tail;
		int urutan = 1;
		
		
		HDLL(){
			head = tail = nullptr;
		}
		
		void enqueue(string data){
			OrderNode* newNode = new OrderNode(data, urutan);
			if (!head){
				head = tail = newNode;
				urutan++;
				return;
			}
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			urutan++;
		}
		
		void dequeue(){
			if(!head){
				cout<<"List kosong";
				return;
			}
			// Cek apakah head adalah node terakhir
			if (head->next == nullptr){
				delete head;
				head = tail = nullptr;
			}else{
				OrderNode* temp = head->next;
				delete head;
				head = temp;	
			}
		}
		
		void deleteName(string name){
			OrderNode* temp = tail;
			if (tail == nullptr){
				return;
			}
			// Traversal
			while(temp->nama != name){
				if (temp->prev == nullptr){
					return;
				}
				temp = temp->prev;
			}
			// Cek apakah temp adalah head
			if (temp == head){
				// Jika head adalah node terakhir maka akan berubah jadi nullptr
				head = temp->next;
				// Cek apakah head == nullptr (berarti hanya 1 node pada linked list sehingga harus ubah tail)
				if (head){
					head->prev = nullptr;
				}else{
					tail == nullptr;
				}
			// Cek apakah temp adalah tail	
			}else if (temp == tail){
				tail = temp->prev;
				// Sama mekanismenya sama yg di head
				if (tail){
					tail->next = nullptr;
				}else{
					head == nullptr;
				}
			// Head bukan tail ataupun head
			}else{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;	
			}
			delete temp;
		}
		
		void display(){
			OrderNode* temp = tail;
			while (temp){
				cout<<temp->nama<<" -> ";
				temp = temp->prev;
			}
			cout<<"NULL";
		}	
		
		~HDLL(){
			OrderNode* temp = tail;
			OrderNode* next = nullptr; // Buat nampung nilai temp selanjutnya setelah dihapus
			while (temp){
				next = temp->prev;
				delete temp;
				temp = next;
			}
		}
};


class PriceNode{
	public:
		int harga;
		PriceNode* prev;
		PriceNode* next;
		HDLL* listpointer = nullptr;
		
		PriceNode(int harga){
			this->harga = harga;
			prev = next = nullptr;
		}
};

class VDLL{
	private:
		PriceNode* head;
		PriceNode* tail;
		int size = 0;
	
	public:
		
		VDLL(){
			head = tail = nullptr;
		}
		
		void addPrice(int harga){
			PriceNode* newNode = new PriceNode(harga);
			newNode->listpointer = new HDLL(); // Bikin link ke HDLL pemesan produk untuk menyimpan OrderNode
			if (!head){
				head = tail = newNode;
				size++;
				return;
			}
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			size++;
		}
		
		void removePrice(int harga){
			PriceNode* temp = tail;
			// Traversal
			while(temp->harga != harga){
				if (temp->prev == nullptr){
					return;
				}
				temp = temp->prev;
			}
			// Cek apakah dia bukan head
			if (temp->prev != nullptr){
				temp->prev->next = temp->next;
				if (temp->next != nullptr){
					temp->next->prev = temp->prev;
				}
			}else{
				// Jika hanya 1 node, maka head akan jadi nullptr
				head = temp->next;
				// apakah head nullptr? (berarti temp node terakhir)
				if (head){
					head->prev = nullptr;
				}else{
					tail == nullptr;
				}
			}
			// Jika ada data di HDLL yang terhubung, panggil destruktor HDLL untuk menghapus data tsb
			if (temp->listpointer != nullptr){
				HDLL* dequeuer = temp->listpointer;
				temp->listpointer = nullptr;
				delete dequeuer;
			}
			delete temp;
			size--;
		}
		
		void editProduct(int position, bool operation, string nama){
			if (size<position){
				cout<<"List terlalu kecil";
				return;
			}
			// Traversal ke PriceNode yg mau diedit
			PriceNode* temp = tail;
			for (int x = 0; x<position; x++){
				temp = temp->prev;
			}
			HDLL* temp2 = temp->listpointer;
			// Operasi Enqueue pada HDLL PriceNode
			if (operation == true){
				temp2->enqueue(nama);	
			// Operasi Dequeue pada HDLL PriceNode
			}else{
				temp2->dequeue();
			}
		}
		
		void display(){
			PriceNode* temp = tail;
			while (temp){
				cout<<temp->harga<<": ";
				if (temp->listpointer != nullptr){
					HDLL* temp2 = temp->listpointer;
					temp2->display();	
				}
				cout<<"\n";
				temp = temp->prev;
			}
		}	
};

int main()
{
	VDLL test;
	test.addPrice(1000000);
	test.addPrice(2500000);
	test.addPrice(3000000);
	test.addPrice(4900000);
	test.editProduct(2, true, "Alfredo");
	test.editProduct(1, true, "Ale");
	test.editProduct(3, true, "Naufal");
	test.editProduct(3, true, "Lingga");
	test.editProduct(0, true, "Zami");
	test.editProduct(1, false, "null");
	test.removePrice(1000000);
	test.display();
	return 0;
}

