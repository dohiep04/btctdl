#include <iostream>
using namespace std;

struct Node {
    int he_so;
    int bac;
    Node* tiep;

    Node(int h, int b) : he_so(h), bac(b), tiep(NULL) {}
};

class DaThuc {
private:
    Node* dau;

public:
    DaThuc() : dau(NULL) {}

    ~DaThuc() {
        Node* hien_tai = dau;
        while (hien_tai) {
            Node* tam = hien_tai;
            hien_tai = hien_tai->tiep;
            delete tam;
        }
    }

    void themHangTu(int he_so, int bac) {
        if (he_so == 0) return;

        Node* nutMoi = new Node(he_so, bac);

        if (!dau || bac > dau->bac) {
            nutMoi->tiep = dau;
            dau = nutMoi;
        } else {
            Node* hien_tai = dau;
            Node* truoc = NULL;

            while (hien_tai && hien_tai->bac > bac) {
                truoc = hien_tai;
                hien_tai = hien_tai->tiep;
            }

            if (hien_tai && hien_tai->bac == bac) {
                hien_tai->he_so += he_so;
                delete nutMoi;
                if (hien_tai->he_so == 0) {
                    if (truoc) {
                        truoc->tiep = hien_tai->tiep;
                    } else {
                        dau = hien_tai->tiep;
                    }
                    delete hien_tai;
                }
            } else {
                nutMoi->tiep = hien_tai;
                if (truoc) {
                    truoc->tiep = nutMoi;
                }
            }
        }
    }

    void hienThi() const {
        if (!dau) {
            cout << "0";
            return;
        }

        Node* hien_tai = dau;
        bool la_dau_tien = true;

        while (hien_tai) {
            if (!la_dau_tien && hien_tai->he_so > 0) {
                cout << " + ";
            }
            cout << hien_tai->he_so;
            if (hien_tai->bac > 0) {
                cout << "x^" << hien_tai->bac;
            }
            hien_tai = hien_tai->tiep;
            la_dau_tien = false;
        }
        cout << endl;
    }
};

int main() {
    DaThuc da_thuc;

    int he_so, bac;
    char tiep_tuc;
    do {
        cout << "Nhap he so: ";
        cin >> he_so;
        cout << "Nhap bac: ";
        cin >> bac;
        da_thuc.themHangTu(he_so, bac);

        cout << "Tiep tuc nhap hang tu khac? (y/n): ";
        cin >> tiep_tuc;
    } while (tiep_tuc == 'y' || tiep_tuc == 'Y');

    cout << "Da thuc: ";
    da_thuc.hienThi();

    return 0;
}

