#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <fstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
}
int stt=0;


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawTable(AdjacencyMatrix ds)
{
    ui->tb_1->setColumnCount(ds.n);
    ui->tb_1->setRowCount(ds.n);
    ui->tb_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ds.n;i++)
        ui->tb_1->setColumnWidth(i,10);
    for(int i=0; i<ds.n;i++)
        for(int j=0;j<ds.n;j++)
        {
            char num_char[10 + sizeof(char)];
            std::sprintf(num_char, "%d", ds.mt[i][j]);
            ui->tb_1->setItem(i,j,new QTableWidgetItem(num_char));
        }
}

void MainWindow::infoAirPort(AirPortList ds)
{
    ui->tb_2->setColumnCount(4);
    ui->tb_2->setRowCount(ds.n);
    QStringList title;
    title<<"MaSB"<<"TenSB"<<"DienThoai"<<"DiaChi";
    ui->tb_2->setHorizontalHeaderLabels(title);
    for(int i=0;i<ds.n;i++)
    {
        char num_char[10 + sizeof(char)];
        std::sprintf(num_char, "%s", ds.ds[i].code);
        ui->tb_2->setItem(i,0,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].name);
        ui->tb_2->setItem(i,1,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].phone);
        ui->tb_2->setItem(i,2,new QTableWidgetItem(num_char));
        std::sprintf(num_char, "%s", ds.ds[i].addr);
        ui->tb_2->setItem(i,3,new QTableWidgetItem(num_char));
    }
}

//Xóa ký tự xuống dòng
void xoaXuongDong(char* str) {
    //Lấy độ dài chuỗi str
    size_t len = strlen(str);

    //Tạo vòng lặp và kiểm tra từng ký tự trong chuỗi
    int i;
    for (i = 0; i <= len; i = i + 1) {
        if (str[i] == '\n') {
            str[i] = NULL; //Thay thế ký tự rỗng nếu tìm thấy.
        }
    }
}

//Đọc một ma trận kề từ file văn bản.
int Read(char* filename, AdjacencyMatrix& g, AirPortList& a)
{
    FILE* f;
    fopen_s(&f, filename, "rt");
    if (f == NULL) return 0;
    fscanf_s(f, "%d", &g.n);
    a.n = g.n;
    int i = 0;
    char tmp[5];
    fgets(tmp, 5, f);
    for (i = 0; i < a.n; i++)
    {
        fgets(a.ds[i].code, 5, f);
        xoaXuongDong(a.ds[i].code);
        fgets(a.ds[i].name, 50, f);
        xoaXuongDong(a.ds[i].name);
        fgets(a.ds[i].phone, 12, f);
        xoaXuongDong(a.ds[i].phone);
        fgets(a.ds[i].addr, 100, f);
        xoaXuongDong(a.ds[i].addr);
    }

    for (i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
        {
            fscanf_s(f, "%d", &g.mt[i][j]);
        }
//Ghi một ma trận kề lên file văn bản.
int Write(char* filename, AdjacencyMatrix g, AirPortList a)
{
    FILE* f;
    fopen_s(&f, filename, "wt");
    if (f == NULL) return 0;
    fprintf(f, "%d", g.n);
    for (int i = 0; i < a.n; i++)
    {
        fprintf(f, "\n");
        fprintf(f, a.ds[i].code);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].name);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].phone);
        fprintf(f, "\n");
        fprintf(f, a.ds[i].addr);
    }

    for (int i = 0; i < g.n; i++)
    {
        fprintf(f, "\n");
        for (int j = 0; j < g.n; j++)
            fprintf(f, "%d\t", g.mt[i][j]);
    }
    fclose(f);
    return 1;
}


//Hàm Dijkstra
int[] Dijkstra(AdjacencyMatrix g, int D, int C) {
	char DanhDau[MAX];
	int i;
	int Nhan[MAX], Truoc[MAX], XP, min;
	for (i = 0; i<g.n; i++) {
		Nhan[i] = INT_MAX;
		DanhDau[i] = 0;
		Truoc[i] = D;
	}
	Nhan[D] = 0;
	DanhDau[D] = 1;
	XP = D;
	int j;
	while (XP != C)
	{
		for (j = 0; j<g.n; j++)
			if (g.mt[XP][j]>0 && Nhan[j]>g.mt[XP][j] + Nhan[XP] && DanhDau[j] == 0)
			{
				Nhan[j] = g.mt[XP][j] + Nhan[XP];
				Truoc[j] = XP;
			}
		min = INT_MAX;
		for (j = 0; j<g.n; j++)
			if (min>Nhan[j] && DanhDau[j] == 0)
			{
				min = Nhan[j];
				XP = j;
			}
		DanhDau[XP] = 1;
	}

    return Truoc

	/*cout << "Duong Di Ngan Nhat La:" << Nhan[C] << endl;
	cout << C << " <- " << Truoc[C];
	i = Truoc[C];
	while (i != D)
	{
		i = Truoc[i];
		cout << " <- " << i;
	}*/
}
//Hàm Prim
int minKey(int key[], bool mstSet[], AdjacencyMatrix g) //ham tim dinh co gia tri nho nhap trong tap dinh
{
    // khởi tạo giá trị nhỏ nhất
    int min = INT_MAX, min_index;

    for (int v = 0; v < g.n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}
void printPrim(int parent[], AdjacencyMatrix g)//ham xuat gia tri duoc luu trong mang parent
{
    cout << "duong di \do dai\n";
    for (int i = 1; i < g.n; i++)
        cout << parent[i] << " - " << i << " \t" << g.mt[i][parent[i]] << " \n";
}
void primMST(AdjacencyMatrix g)
{

    int parent[5]; // luu tru mang


    int key[5]; //luu gia tri cac canh co trong so nho nhat


    bool mstSet[5];// luu cac tap dinh co trong ma tran


    for (int i = 0; i < g.n; i++)
        key[i] = INT_MAX, mstSet[i] = false;

//Hàm kruskal
void printMST(int a[], int b[], int weight[], AdjacencyMatrix g) 
{
	int Minweight = 0; 
	for (int i = 0; i < g.n - 1; i++)
	{
		cout << "duong di: " << a[i] << "-" << b[i] << " "
			<< "do dai: " << weight[i] << endl;
		Minweight += weight[i];
	}
	cout << "gia tri duong di nho nhat " << Minweight << endl; 
}

int findParent(int node) {
	while (parent[node] >= 0)
		node = parent[node];

	return node;
}

int findParentPathCompression(int node)
{
	if (node == parent[node]) return node;
	return parent[node] = findParentPathCompression(parent[node]);
}


void kruskal(AdjacencyMatrix g) 
{
	fill_n(parent, g.n, -1);
	int u, v, k = 0, count = 0;
	int firstNode, secondNode;
	int a[6];
	int b[6]; 
	int weight[7]; 
	int minimum;

	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
			if (g.mt[i][j] == 0) 
				g.mt[i][j] = INT_MAX; 

	while (count < g.n - 1)
	{
		minimum = INT_MAX;

		for (int i = 0; i < g.n; i++)
		{
			for (int j = 0; j < g.n; j++)
			{
				if (g.mt[i][j] < minimum)
				{
					minimum = g.mt[i][j]; 
					firstNode = i; 
					secondNode = j; 
				}
			}
		}

		u = findParent(firstNode);
		v = findParent(secondNode);


		if (u != v) 
		{
			parent[v] = u;
			a[k] = firstNode; 
			b[k] = secondNode; 
			weight[k] = g.mt[firstNode][secondNode]; 
			count++;
			k++;
		}

		g.mt[firstNode][secondNode] = g.mt[secondNode][firstNode] = INT_MAX; 
	}

	printMST(a, b, weight, g); 
}

    key[0] = 0;
    parent[0] = -1; // //khoi tao nut goc ma tran


    for (int count = 0; count < g.n - 1; count++)
    {

        int u = minKey(key, mstSet, g);


        mstSet[u] = true;

        for (int v = 0; v < g.n; v++)


            if (g.mt[u][v] && mstSet[v] == false && g.mt[u][v] < key[v])
                parent[v] = u, key[v] = g.mt[u][v];
    }


    printPrim(parent, g);
}

void MainWindow::on_btn_Read_clicked()
{
    stt=1;
    ui->txt_FileName->setEnabled(true);
    ui->btn_OK->setEnabled(true);

}


void MainWindow::on_btn_OK_clicked()
{
    if(stt==1)
    {

        QString a;
        a = ui->txt_FileName->text();
        QByteArray ba = a.toLocal8Bit();
        const char *str = ba.data();
        QString b = QString::number(Read((char*)str,am,sb));
        //ui->label_2->setText(b);
        drawTable(am);
        infoAirPort(sb);
        ui->txt_FileName->setEnabled(false);
        ui->btn_OK->setEnabled(false);
        stt=0;
    }
    else if(stt==2)
    {
        QString a;
        a = ui->txt_FileName->text();
        QByteArray ba = a.toLocal8Bit();
        const char *str = ba.data();
        QString b = QString::number(Write((char*)str,am,sb));
        ui->label_2->setText(b);
        ui->txt_FileName->setEnabled(false);
        ui->btn_OK->setEnabled(false);
        stt=0;
    }
}

void MainWindow::on_btn_Xuat_clicked()
{

}


void MainWindow::on_btn_Add_clicked()
{

}


void MainWindow::on_btn_Nhap_clicked()
{
    ui->txt_Code->setEnabled(true);
    ui->txt_Name->setEnabled(true);
    ui->txt_Phone->setEnabled(true);
    ui->txt_Addr->setEnabled(true);
    ui->btn_OK_2->setEnabled(true);
}


void MainWindow::on_btn_OK_2_clicked()
{

    QString a;
    a = ui->txt_Code->text();
    QByteArray ba = a.toLocal8Bit();
    const char *str = ba.data();
    char temp[5];
    strncpy(temp,str,5);
    if(checkCode(temp)==true)
        ui->label_2->setText("Ma SB da ton tai!");
    else
    {
        strcpy(sb.ds[sb.n].code,temp);
        //ten
        a=ui->txt_Name->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpName[50];
        strncpy(tmpName,str,50);
        strcpy(sb.ds[sb.n].name,tmpName);
        //dien thoai
        a=ui->txt_Phone->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpPhone[12];
        strncpy(tmpPhone,str,12);
        strcpy(sb.ds[sb.n].phone,tmpPhone);
        //dia chi
        a=ui->txt_Addr->text();
        ba=a.toLocal8Bit();
        str=ba.data();
        char tmpAddr[100];
        strncpy(tmpAddr,str,100);
        strcpy(sb.ds[sb.n].addr,tmpAddr);
        sb.n++;
        am.n++;
        //khoi tao dong moi cho ma tran
        for(int i=0;i<am.n;i++)
            am.mt[am.n-1][i]=0;
        ui->label_2->setText("Them thanh cong!");
        drawTable(am);
        infoAirPort(sb);
    }
}
bool checkCode(char* code)
{
    for(int i=0;i<sb.n;i++)
    {
        if(strcmp(sb.ds[i].code,code)==0)
            return true;
    }
    return false;
}


void MainWindow::on_btn_Write_clicked()
{
    stt=2;
    ui->txt_FileName->setEnabled(true);
    ui->btn_OK->setEnabled(true);
}

