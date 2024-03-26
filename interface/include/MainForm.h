#pragma once

#include <msclr/marshal_cppstd.h>
#include "TableController.h"
#include "MyExpression.h"
#include "Polinom.h"

namespace TableLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
    using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
        const int VIEW_SIZE = 14;
		MainForm(void)
		{
            win1251 = System::Text::Encoding::GetEncoding(1251);
            utf8 = gcnew System::Text::UTF8Encoding(false, false);//System::Text::Encoding::UTF8;
            tableController = new TableController<std::string, TPolinom>;
            dataViews = gcnew array <Tuple<String^, DataGridView^>^>(VIEW_SIZE);

			InitializeComponent();
            dataViews[0] = gcnew Tuple<String^, DataGridView^>(this->tabPage1->Text, this->dataGridView1);
            dataViews[1] = gcnew Tuple<String^, DataGridView^>(this->tabPage2->Text, this->dataGridView2);
            dataViews[2] = gcnew Tuple<String^, DataGridView^>(this->tabPage3->Text, this->dataGridView3);
            dataViews[3] = gcnew Tuple<String^, DataGridView^>(this->tabPage4->Text, this->dataGridView4);
            dataViews[4] = gcnew Tuple<String^, DataGridView^>(this->tabPage5->Text, this->dataGridView5);
            dataViews[5] = gcnew Tuple<String^, DataGridView^>(this->tabPage6->Text, this->dataGridView6);
            dataViews[6] = gcnew Tuple<String^, DataGridView^>(this->tabPage7->Text, this->dataGridView7);

            dataViews[7] = gcnew Tuple<String^, DataGridView^>(this->tabPage1->Text, this->dataGridView8);
            dataViews[8] = gcnew Tuple<String^, DataGridView^>(this->tabPage2->Text, this->dataGridView9);
            dataViews[9] = gcnew Tuple<String^, DataGridView^>(this->tabPage3->Text, this->dataGridView10);
            dataViews[10] = gcnew Tuple<String^, DataGridView^>(this->tabPage4->Text, this->dataGridView11);
            dataViews[11] = gcnew Tuple<String^, DataGridView^>(this->tabPage5->Text, this->dataGridView12);
            dataViews[12] = gcnew Tuple<String^, DataGridView^>(this->tabPage6->Text, this->dataGridView13);
            dataViews[13] = gcnew Tuple<String^, DataGridView^>(this->tabPage7->Text, this->dataGridView14);

            this->comboBox1->Items->Add(this->tabPage1->Text);
            this->comboBox1->Items->Add(this->tabPage2->Text);
            this->comboBox1->Items->Add(this->tabPage3->Text);
            this->comboBox1->Items->Add(this->tabPage4->Text);
            this->comboBox1->Items->Add(this->tabPage5->Text);
            this->comboBox1->Items->Add(this->tabPage6->Text);
            this->comboBox1->Items->Add(this->tabPage7->Text);

            tableController->AddTable(context.marshal_as<std::string>(this->tabPage1->Text), new VectorTable<std::string, TPolinom>());
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage2->Text), new OrderedTable<std::string, TPolinom>());
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage3->Text), new ListTable<std::string, TPolinom>());
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage4->Text), new AVLTreeTable<std::string, TPolinom>()); 
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage5->Text), new RedBlackTreeTable<std::string, TPolinom>());
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage6->Text), new ChainHashTable<std::string, TPolinom>());
            tableController->AddTable(context.marshal_as<std::string>(this->tabPage7->Text), new RepeatMixingTable<std::string, TPolinom>());

            TPolinom pol1;
            pol1.AddMonom(TMonom(3.2, 3, new int[] {2, 3, 1}));
            pol1.AddMonom(TMonom(-1.3, 3, new int[] {1, 0, 4}));

            TPolinom pol2;
            pol2.AddMonom(TMonom(-3.2, 3, new int[] {2, 3, 1}));
            pol2.AddMonom(TMonom(1.3, 3, new int[] {1, 0, 4}));
            
            TPolinom const6;
            const6.AddMonom(TMonom(6, 3, new int[] {0,0,0}));
            
            TPolinom q;
            q.AddMonom(TMonom(4, 3, new int[] {2, 0, 0}));
            
            tableController->Insert("pol1", pol1);
            tableController->Insert("pol2", pol2);
            tableController->Insert("const6", const6);
            tableController->Insert("q", q);

            UpdateAllData();

            this->textBox1->Text = "new_pol";
            this->richTextBox1->Text = "2 * pol1 + 2 * pol2 + 3.6 * q - const6";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
                delete tableController;
                delete[] dataViews;
                delete utf8;
                delete win1251;
			}
		}

	private:
        System::Text::Encoding^ win1251;
        System::Text::Encoding^ utf8;
        msclr::interop::marshal_context context;

        TableController<std::string, TPolinom>* tableController;
        array <Tuple<String^, DataGridView^>^>^ dataViews;
        /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::RichTextBox^ richTextBox2;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::TabPage^ tabPage2;
    private: System::Windows::Forms::TabPage^ tabPage1;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom;
    private: System::Windows::Forms::TabControl^ tabControl1;
    private: System::Windows::Forms::TabPage^ tabPage3;
    private: System::Windows::Forms::TabPage^ tabPage4;
    private: System::Windows::Forms::TabPage^ tabPage5;
    private: System::Windows::Forms::TabPage^ tabPage6;
    private: System::Windows::Forms::TabPage^ tabPage7;
    private: System::Windows::Forms::TabPage^ tabPage8;
    private: System::Windows::Forms::DataGridView^ dataGridView2;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name1;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom1;
    private: System::Windows::Forms::DataGridView^ dataGridView3;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name2;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom2;
    private: System::Windows::Forms::DataGridView^ dataGridView4;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name3;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom3;
    private: System::Windows::Forms::DataGridView^ dataGridView5;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name4;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom4;
    private: System::Windows::Forms::DataGridView^ dataGridView6;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name5;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom5;
    private: System::Windows::Forms::DataGridView^ dataGridView7;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name6;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom6;
    private: System::Windows::Forms::DataGridView^ dataGridView8;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name7;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom7;
    private: System::Windows::Forms::DataGridView^ dataGridView9;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name8;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom8;
    private: System::Windows::Forms::DataGridView^ dataGridView10;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name9;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom9;
    private: System::Windows::Forms::DataGridView^ dataGridView11;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name10;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom10;
    private: System::Windows::Forms::DataGridView^ dataGridView12;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name11;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom11;
    private: System::Windows::Forms::DataGridView^ dataGridView13;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name12;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom12;
    private: System::Windows::Forms::DataGridView^ dataGridView14;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ name13;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ polinom13;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::ComboBox^ comboBox1;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
            this->name1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
            this->name2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
            this->name3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView5 = (gcnew System::Windows::Forms::DataGridView());
            this->name4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView6 = (gcnew System::Windows::Forms::DataGridView());
            this->name5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView7 = (gcnew System::Windows::Forms::DataGridView());
            this->name6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->dataGridView8 = (gcnew System::Windows::Forms::DataGridView());
            this->name7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView9 = (gcnew System::Windows::Forms::DataGridView());
            this->name8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView10 = (gcnew System::Windows::Forms::DataGridView());
            this->name9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView11 = (gcnew System::Windows::Forms::DataGridView());
            this->name10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView12 = (gcnew System::Windows::Forms::DataGridView());
            this->name11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView13 = (gcnew System::Windows::Forms::DataGridView());
            this->name12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridView14 = (gcnew System::Windows::Forms::DataGridView());
            this->name13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->polinom13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
            this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
            this->panel1->SuspendLayout();
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->tabPage2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
            this->tabPage1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->tabControl1->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->groupBox1);
            this->panel1->Controls->Add(this->label1);
            this->panel1->Controls->Add(this->groupBox2);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->panel1->Location = System::Drawing::Point(0, 858);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(1898, 286);
            this->panel1->TabIndex = 0;
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->label4);
            this->groupBox1->Controls->Add(this->richTextBox2);
            this->groupBox1->Controls->Add(this->button2);
            this->groupBox1->Controls->Add(this->textBox2);
            this->groupBox1->Controls->Add(this->label3);
            this->groupBox1->Location = System::Drawing::Point(946, 6);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(940, 268);
            this->groupBox1->TabIndex = 3;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = RuStr("Вставка");
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(16, 78);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(123, 30);
            this->label4->TabIndex = 9;
            this->label4->Text = RuStr("Полином:");
            // 
            // richTextBox2
            // 
            this->richTextBox2->Location = System::Drawing::Point(12, 101);
            this->richTextBox2->Name = L"richTextBox2";
            this->richTextBox2->ReadOnly = true;
            this->richTextBox2->Size = System::Drawing::Size(917, 150);
            this->richTextBox2->TabIndex = 8;
            this->richTextBox2->Text = L"";
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(695, 28);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(228, 39);
            this->button2->TabIndex = 6;
            this->button2->Text = RuStr("Найти полином");
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
            // 
            // textBox2
            // 
            this->textBox2->Location = System::Drawing::Point(144, 34);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(545, 26);
            this->textBox2->TabIndex = 5;
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(16, 37);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(185, 30);
            this->label3->TabIndex = 7;
            this->label3->Text = RuStr("Имя полинома:");
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(18, 37);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(150, 30);
            this->label1->TabIndex = 3;
            this->label1->Text = RuStr("Выражение:");
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Location = System::Drawing::Point(1380, 398);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(150, 30);
            this->label12->TabIndex = 3;
            this->label12->Text = RuStr("Активная таблица:");
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->button1);
            this->groupBox2->Controls->Add(this->richTextBox1);
            this->groupBox2->Controls->Add(this->textBox1);
            this->groupBox2->Controls->Add(this->label2);
            this->groupBox2->Location = System::Drawing::Point(12, 6);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(928, 268);
            this->groupBox2->TabIndex = 4;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = RuStr("Поиск");
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(685, 212);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(228, 39);
            this->button1->TabIndex = 2;
            this->button1->Text = RuStr("Добавить полином");
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
            // 
            // richTextBox1
            // 
            this->richTextBox1->Location = System::Drawing::Point(6, 54);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->Size = System::Drawing::Size(916, 148);
            this->richTextBox1->TabIndex = 1;
            this->richTextBox1->Text = L"";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(134, 218);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(545, 26);
            this->textBox1->TabIndex = 0;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(6, 221);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(185, 30);
            this->label2->TabIndex = 4;
            this->label2->Text = RuStr("Имя полинома:");
            // 
            // tabPage2
            // 
            this->tabPage2->Controls->Add(this->dataGridView2);
            this->tabPage2->Location = System::Drawing::Point(4, 29);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(3);
            this->tabPage2->Size = System::Drawing::Size(1890, 825);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->UseVisualStyleBackColor = true;
            this->tabPage2->Text = RuStr("Сортированная таблица");
            // 
            // tabPage1
            // 
            this->tabPage1->Controls->Add(this->dataGridView1);
            this->tabPage1->Location = System::Drawing::Point(4, 29);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(3);
            this->tabPage1->Size = System::Drawing::Size(1890, 825);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->UseVisualStyleBackColor = true;
            this->tabPage1->Text = RuStr("Векторная таблица");
            // 
            // dataGridView2
            // 
            this->dataGridView2->AllowUserToAddRows = false;
            this->dataGridView2->AllowUserToDeleteRows = false;
            this->dataGridView2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name1,
                    this->polinom1
            });
            this->dataGridView2->Location = System::Drawing::Point(0, 0);
            this->dataGridView2->Name = L"dataGridView2";
            this->dataGridView2->RowHeadersWidth = 20;
            this->dataGridView2->RowTemplate->Height = 28;
            this->dataGridView2->Size = System::Drawing::Size(1891, 825);
            this->dataGridView2->TabIndex = 0;
            this->dataGridView2->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name1
            // 
            this->name1->HeaderText= RuStr("Имя");
            this->name1->MinimumWidth = 8;
            this->name1->Name = L"name1";
            this->name1->ReadOnly = true;
            this->name1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name1->Width = 150;
            // 
            // polinom1
            // 
            this->polinom1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom1->HeaderText = RuStr("Полином");
            this->polinom1->MinimumWidth = 8;
            this->polinom1->Name = L"polinom1";
            this->polinom1->ReadOnly = true;
            this->polinom1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView1
            // 
            this->dataGridView1->AllowUserToAddRows = false;
            this->dataGridView1->AllowUserToDeleteRows = false;
            this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->name, this->polinom });
            this->dataGridView1->Location = System::Drawing::Point(0, 0);
            this->dataGridView1->Name = L"dataGridView1";
            dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
            dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
            dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
            dataGridViewCellStyle1->Padding = System::Windows::Forms::Padding(62);
            dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
            dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
            dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
            this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView1->RowHeadersWidth = 20;
            this->dataGridView1->RowTemplate->Height = 28;
            this->dataGridView1->Size = System::Drawing::Size(1891, 825);
            this->dataGridView1->TabIndex = 0;
            this->dataGridView1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name
            // 
            this->name->MinimumWidth = 8;
            this->name->Name = L"name";
            this->name->HeaderText= RuStr("Имя");
            this->name->ReadOnly = true;
            this->name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name->Width = 150;
            // 
            // polinom
            // 
            this->polinom->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom->MinimumWidth = 8;
            this->polinom->HeaderText = RuStr("Полином");
            this->polinom->Name = L"polinom";
            this->polinom->ReadOnly = true;
            this->polinom->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // tabControl1
            // 
            this->tabControl1->Controls->Add(this->tabPage8);
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Controls->Add(this->tabPage3);
            this->tabControl1->Controls->Add(this->tabPage4);
            this->tabControl1->Controls->Add(this->tabPage5);
            this->tabControl1->Controls->Add(this->tabPage6);
            this->tabControl1->Controls->Add(this->tabPage7);
            this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tabControl1->Location = System::Drawing::Point(0, 0);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(1898, 858);
            this->tabControl1->TabIndex = 1;
            this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::tabControl1_SelectedIndexChanged);
            // 
            // tabPage8
            //
            this->tabPage8->Controls->Add(this->dataGridView8);
            this->tabPage8->Controls->Add(this->dataGridView9);
            this->tabPage8->Controls->Add(this->dataGridView10);
            this->tabPage8->Controls->Add(this->dataGridView11);
            this->tabPage8->Controls->Add(this->dataGridView12);
            this->tabPage8->Controls->Add(this->dataGridView13);
            this->tabPage8->Controls->Add(this->dataGridView14);
            this->tabPage8->Controls->Add(this->comboBox1);
            this->tabPage8->Controls->Add(this->label5);
            this->tabPage8->Controls->Add(this->label6);
            this->tabPage8->Controls->Add(this->label7);
            this->tabPage8->Controls->Add(this->label8);
            this->tabPage8->Controls->Add(this->label9);
            this->tabPage8->Controls->Add(this->label10);
            this->tabPage8->Controls->Add(this->label11);
            this->tabPage8->Controls->Add(this->label12);
            this->tabPage8->Location = System::Drawing::Point(4, 29);
            this->tabPage8->Name = L"tabPage8";
            this->tabPage8->Padding = System::Windows::Forms::Padding(3);
            this->tabPage8->Size = System::Drawing::Size(1890, 825);
            this->tabPage8->TabIndex = 7;
            this->tabPage8->UseVisualStyleBackColor = true;
            this->tabPage8->Text = RuStr("Дешборд");
            // 
            // tabPage3
            //
            this->tabPage3->Controls->Add(this->dataGridView3);
            this->tabPage3->Location = System::Drawing::Point(4, 29);
            this->tabPage3->Name = L"tabPage3";
            this->tabPage3->Padding = System::Windows::Forms::Padding(3);
            this->tabPage3->Size = System::Drawing::Size(1890, 825);
            this->tabPage3->TabIndex = 2;
            this->tabPage3->UseVisualStyleBackColor = true;
            this->tabPage3->Text = RuStr("Таблица на списках");
            // 
            // dataGridView3
            // 
            this->dataGridView3->AllowUserToAddRows = false;
            this->dataGridView3->AllowUserToDeleteRows = false;
            this->dataGridView3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name2,
                    this->polinom2
            });
            this->dataGridView3->Location = System::Drawing::Point(0, 0);
            this->dataGridView3->Name = L"dataGridView3";
            this->dataGridView3->RowHeadersWidth = 20;
            this->dataGridView3->RowTemplate->Height = 28;
            this->dataGridView3->Size = System::Drawing::Size(1891, 825);
            this->dataGridView3->TabIndex = 0;
            this->dataGridView3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            this->dataGridView3->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            // 
            // name2
            // 
            this->name2->HeaderText = RuStr("Имя");
            this->name2->MinimumWidth = 8;
            this->name2->Name = L"name2";
            this->name2->ReadOnly = true;
            this->name2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name2->Width = 150;
            // 
            // polinom2
            // 
            this->polinom2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom2->HeaderText = RuStr("Полином");
            this->polinom2->MinimumWidth = 8;
            this->polinom2->Name = L"polinom2";
            this->polinom2->ReadOnly = true;
            this->polinom2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // tabPage4
            // 
            this->tabPage4->Controls->Add(this->dataGridView4);
            this->tabPage4->Location = System::Drawing::Point(4, 29);
            this->tabPage4->Name = L"tabPage4";
            this->tabPage4->Padding = System::Windows::Forms::Padding(3);
            this->tabPage4->Size = System::Drawing::Size(1890, 825);
            this->tabPage4->TabIndex = 3;
            this->tabPage4->UseVisualStyleBackColor = true;
            this->tabPage4->Text = RuStr("АВЛ-дерево");
            // 
            // dataGridView4
            // 
            this->dataGridView4->AllowUserToAddRows = false;
            this->dataGridView4->AllowUserToDeleteRows = false;
            this->dataGridView4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView4->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name3,
                    this->polinom3
            });
            this->dataGridView4->Location = System::Drawing::Point(0, 0);
            this->dataGridView4->Name = L"dataGridView4";
            this->dataGridView4->RowHeadersWidth = 20;
            this->dataGridView4->RowTemplate->Height = 28;
            this->dataGridView4->Size = System::Drawing::Size(1891, 825);
            this->dataGridView4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            this->dataGridView4->TabIndex = 0;
            this->dataGridView4->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            // 
            // name3
            // 
            this->name3->HeaderText = RuStr("Имя");
            this->name3->MinimumWidth = 8;
            this->name3->Name = L"name3";
            this->name3->ReadOnly = true;
            this->name3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name3->Width = 150;
            // 
            // polinom3
            // 
            this->polinom3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom3->HeaderText = RuStr("Полином");
            this->polinom3->MinimumWidth = 8;
            this->polinom3->Name = L"polinom3";
            this->polinom3->ReadOnly = true;
            this->polinom3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // tabPage5
            // 
            this->tabPage5->Controls->Add(this->dataGridView5);
            this->tabPage5->Location = System::Drawing::Point(4, 29);
            this->tabPage5->Name = L"tabPage5";
            this->tabPage5->Padding = System::Windows::Forms::Padding(3);
            this->tabPage5->Size = System::Drawing::Size(1890, 825);
            this->tabPage5->TabIndex = 4;
            this->tabPage5->UseVisualStyleBackColor = true;
            this->tabPage5->Text = RuStr("Красно-черное дерево");
            // 
            // dataGridView5
            // 
            this->dataGridView5->AllowUserToAddRows = false;
            this->dataGridView5->AllowUserToDeleteRows = false;
            this->dataGridView5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView5->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView5->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name4,
                    this->polinom4
            });
            this->dataGridView5->Location = System::Drawing::Point(0, 0);
            this->dataGridView5->Name = L"dataGridView5";
            this->dataGridView5->RowHeadersWidth = 20;
            this->dataGridView5->RowTemplate->Height = 28;
            this->dataGridView5->Size = System::Drawing::Size(1891, 825);
            this->dataGridView5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            this->dataGridView5->TabIndex = 0;
            this->dataGridView5->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            // 
            // name4
            // 
            this->name4->HeaderText = RuStr("Имя");
            this->name4->MinimumWidth = 8;
            this->name4->Name = L"name4";
            this->name4->ReadOnly = true;
            this->name4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name4->Width = 150;
            // 
            // polinom4
            // 
            this->polinom4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom4->HeaderText = RuStr("Полином");
            this->polinom4->MinimumWidth = 8;
            this->polinom4->Name = L"polinom4";
            this->polinom4->ReadOnly = true;
            this->polinom4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // tabPage6
            // 
            this->tabPage6->Controls->Add(this->dataGridView6);
            this->tabPage6->Location = System::Drawing::Point(4, 29);
            this->tabPage6->Name = L"tabPage6";
            this->tabPage6->Padding = System::Windows::Forms::Padding(3);
            this->tabPage6->Size = System::Drawing::Size(1890, 825);
            this->tabPage6->TabIndex = 5;
            this->tabPage6->UseVisualStyleBackColor = true;
            this->tabPage6->Text = RuStr("Хэш на звеньях");
            // 
            // dataGridView6
            // 
            this->dataGridView6->AllowUserToAddRows = false;
            this->dataGridView6->AllowUserToDeleteRows = false;
            this->dataGridView6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->dataGridView6->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView6->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name5,
                    this->polinom5
            });
            this->dataGridView6->Location = System::Drawing::Point(0, 0);
            this->dataGridView6->Name = L"dataGridView6";
            this->dataGridView6->RowHeadersWidth = 20;
            this->dataGridView6->RowTemplate->Height = 28;
            this->dataGridView6->Size = System::Drawing::Size(1891, 825);
            this->dataGridView6->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            this->dataGridView6->TabIndex = 0;
            this->dataGridView6->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            // 
            // name5
            // 
            this->name5->HeaderText = RuStr("Имя");
            this->name5->MinimumWidth = 8;
            this->name5->Name = L"name5";
            this->name5->ReadOnly = true;
            this->name5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name5->Width = 150;
            // 
            // polinom5
            // 
            this->polinom5->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom5->HeaderText = RuStr("Полином");
            this->polinom5->MinimumWidth = 8;
            this->polinom5->Name = L"polinom5";
            this->polinom5->ReadOnly = true;
            this->polinom5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // tabPage7
            // 
            this->tabPage7->Controls->Add(this->dataGridView7);
            this->tabPage7->Location = System::Drawing::Point(4, 29);
            this->tabPage7->Name = L"tabPage7";
            this->tabPage7->Padding = System::Windows::Forms::Padding(3);
            this->tabPage7->Size = System::Drawing::Size(1890, 825);
            this->tabPage7->TabIndex = 6;
            this->tabPage7->UseVisualStyleBackColor = true;
            this->tabPage7->Text = RuStr("Повторное перемешивание");
            // 
            // dataGridView7
            // 
            this->dataGridView7->AllowUserToAddRows = false;
            this->dataGridView7->AllowUserToDeleteRows = false;
            this->dataGridView7->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView7->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name6,
                    this->polinom6
            });
            this->dataGridView7->Location = System::Drawing::Point(0, 0);
            this->dataGridView7->Name = L"dataGridView7";
            this->dataGridView7->RowHeadersWidth = 20;
            this->dataGridView7->RowTemplate->Height = 28;
            this->dataGridView7->Size = System::Drawing::Size(1891, 825);
            this->dataGridView7->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            this->dataGridView7->TabIndex = 0;
            this->dataGridView7->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            // 
            // name6
            // 
            this->name6->HeaderText = RuStr("Имя");
            this->name6->MinimumWidth = 8;
            this->name6->Name = L"name6";
            this->name6->ReadOnly = true;
            this->name6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name6->Width = 150;
            // 
            // polinom6
            // 
            this->polinom6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom6->HeaderText = RuStr("Полином");
            this->polinom6->MinimumWidth = 8;
            this->polinom6->Name = L"polinom6";
            this->polinom6->ReadOnly = true;
            this->polinom6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView8
            // 
            this->dataGridView8->AllowUserToAddRows = false;
            this->dataGridView8->AllowUserToDeleteRows = false;
            this->dataGridView8->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView8->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name7,
                    this->polinom7
            });
            this->dataGridView8->Location = System::Drawing::Point(0, 30);
            this->dataGridView8->Name = L"dataGridView8";
            this->dataGridView8->RowHeadersWidth = 20;
            this->dataGridView8->RowTemplate->Height = 28;
            this->dataGridView8->Size = System::Drawing::Size(450, 360);
            this->dataGridView8->TabIndex = 0;
            this->dataGridView8->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView8->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name7
            // 
            this->name7->HeaderText = RuStr("Имя");
            this->name7->MinimumWidth = 8;
            this->name7->Name = L"name7";
            this->name7->ReadOnly = true;
            this->name7->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name7->Width = 80;
            // 
            // polinom7
            // 
            this->polinom7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom7->HeaderText = RuStr("Полином");
            this->polinom7->MinimumWidth = 8;
            this->polinom7->Name = L"polinom7";
            this->polinom7->ReadOnly = true;
            this->polinom7->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView9
            // 
            this->dataGridView9->AllowUserToAddRows = false;
            this->dataGridView9->AllowUserToDeleteRows = false;
            this->dataGridView9->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView9->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name8,
                    this->polinom8
            });
            this->dataGridView9->Location = System::Drawing::Point(460, 30);
            this->dataGridView9->Name = L"dataGridView9";
            this->dataGridView9->RowHeadersWidth = 20;
            this->dataGridView9->RowTemplate->Height = 28;
            this->dataGridView9->Size = System::Drawing::Size(450, 360);
            this->dataGridView9->TabIndex = 0;
            this->dataGridView9->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView9->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name8
            // 
            this->name8->HeaderText = RuStr("Имя");
            this->name8->MinimumWidth = 8;
            this->name8->Name = L"name8";
            this->name8->ReadOnly = true;
            this->name8->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name8->Width = 80;
            // 
            // polinom8
            // 
            this->polinom8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom8->HeaderText = RuStr("Полином");
            this->polinom8->MinimumWidth = 8;
            this->polinom8->Name = L"polinom8";
            this->polinom8->ReadOnly = true;
            this->polinom8->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView10
            // 
            this->dataGridView10->AllowUserToAddRows = false;
            this->dataGridView10->AllowUserToDeleteRows = false;
            this->dataGridView10->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView10->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name9,
                    this->polinom9
            });
            this->dataGridView10->Location = System::Drawing::Point(920, 30);
            this->dataGridView10->Name = L"dataGridView10";
            this->dataGridView10->RowHeadersWidth = 20;
            this->dataGridView10->RowTemplate->Height = 28;
            this->dataGridView10->Size = System::Drawing::Size(450, 360);
            this->dataGridView10->TabIndex = 0;
            this->dataGridView10->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView10->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name9
            // 
            this->name9->HeaderText = RuStr("Имя");
            this->name9->MinimumWidth = 8;
            this->name9->Name = L"name9";
            this->name9->ReadOnly = true;
            this->name9->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name9->Width = 80;
            // 
            // polinom9
            // 
            this->polinom9->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom9->HeaderText = RuStr("Полином");
            this->polinom9->MinimumWidth = 8;
            this->polinom9->Name = L"polinom9";
            this->polinom9->ReadOnly = true;
            this->polinom9->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView11
            // 
            this->dataGridView11->AllowUserToAddRows = false;
            this->dataGridView11->AllowUserToDeleteRows = false;
            this->dataGridView11->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView11->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name10,
                    this->polinom10
            });
            this->dataGridView11->Location = System::Drawing::Point(1370, 30);
            this->dataGridView11->Name = L"dataGridView11";
            this->dataGridView11->RowHeadersWidth = 20;
            this->dataGridView11->RowTemplate->Height = 28;
            this->dataGridView11->Size = System::Drawing::Size(450, 360);
            this->dataGridView11->TabIndex = 0;
            this->dataGridView11->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView11->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name10
            // 
            this->name10->HeaderText = RuStr("Имя");
            this->name10->MinimumWidth = 8;
            this->name10->Name = L"name10";
            this->name10->ReadOnly = true;
            this->name10->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name10->Width = 80;
            // 
            // polinom10
            // 
            this->polinom10->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom10->HeaderText = RuStr("Полином");
            this->polinom10->MinimumWidth = 8;
            this->polinom10->Name = L"polinom10";
            this->polinom10->ReadOnly = true;
            this->polinom10->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView12
            // 
            this->dataGridView12->AllowUserToAddRows = false;
            this->dataGridView12->AllowUserToDeleteRows = false;
            this->dataGridView12->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView12->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name11,
                    this->polinom11
            });
            this->dataGridView12->Location = System::Drawing::Point(0, 420);
            this->dataGridView12->Name = L"dataGridView12";
            this->dataGridView12->RowHeadersWidth = 20;
            this->dataGridView12->RowTemplate->Height = 28;
            this->dataGridView12->Size = System::Drawing::Size(450, 360);
            this->dataGridView12->TabIndex = 0;
            this->dataGridView12->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView12->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name11
            // 
            this->name11->HeaderText = RuStr("Имя");
            this->name11->MinimumWidth = 8;
            this->name11->Name = L"name11";
            this->name11->ReadOnly = true;
            this->name11->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name11->Width = 80;
            // 
            // polinom11
            // 
            this->polinom11->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom11->HeaderText = RuStr("Полином");
            this->polinom11->MinimumWidth = 8;
            this->polinom11->Name = L"polinom11";
            this->polinom11->ReadOnly = true;
            this->polinom11->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView13
            // 
            this->dataGridView13->AllowUserToAddRows = false;
            this->dataGridView13->AllowUserToDeleteRows = false;
            this->dataGridView13->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView13->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name12,
                    this->polinom12
            });
            this->dataGridView13->Location = System::Drawing::Point(460, 420);
            this->dataGridView13->Name = L"dataGridView13";
            this->dataGridView13->RowHeadersWidth = 20;
            this->dataGridView13->RowTemplate->Height = 28;
            this->dataGridView13->Size = System::Drawing::Size(450, 360);
            this->dataGridView13->TabIndex = 0;
            this->dataGridView13->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView13->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name12
            // 
            this->name12->HeaderText = RuStr("Имя");
            this->name12->MinimumWidth = 8;
            this->name12->Name = L"name12";
            this->name12->ReadOnly = true;
            this->name12->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name12->Width = 80;
            // 
            // polinom12
            // 
            this->polinom12->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom12->HeaderText = RuStr("Полином");
            this->polinom12->MinimumWidth = 8;
            this->polinom12->Name = L"polinom12";
            this->polinom12->ReadOnly = true;
            this->polinom12->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // dataGridView14
            // 
            this->dataGridView14->AllowUserToAddRows = false;
            this->dataGridView14->AllowUserToDeleteRows = false;
            this->dataGridView14->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView14->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
                this->name13,
                    this->polinom13
            });
            this->dataGridView14->Location = System::Drawing::Point(920, 420);
            this->dataGridView14->Name = L"dataGridView14";
            this->dataGridView14->RowHeadersWidth = 20;
            this->dataGridView14->RowTemplate->Height = 28;
            this->dataGridView14->Size = System::Drawing::Size(450, 360);
            this->dataGridView14->TabIndex = 0;
            this->dataGridView14->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this->dataGridView14->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
            // 
            // name13
            // 
            this->name13->HeaderText = RuStr("Имя");
            this->name13->MinimumWidth = 8;
            this->name13->Name = L"name13";
            this->name13->ReadOnly = true;
            this->name11->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            this->name11->Width = 80;
            // 
            // polinom13
            // 
            this->polinom13->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->polinom13->HeaderText = RuStr("Полином");
            this->polinom13->MinimumWidth = 8;
            this->polinom13->Name = L"polinom13";
            this->polinom13->ReadOnly = true;
            this->polinom13->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(0, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(185, 30);
            this->label5->TabIndex = 4;
            this->label5->Text = this->tabPage1->Text;
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(460, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(185, 30);
            this->label6->TabIndex = 4;
            this->label6->Text = this->tabPage2->Text;
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(920, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(185, 30);
            this->label7->TabIndex = 4;
            this->label7->Text = this->tabPage3->Text;
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(1380, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(185, 30);
            this->label8->TabIndex = 4;
            this->label8->Text = this->tabPage4->Text;
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(0, 400);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(185, 30);
            this->label9->TabIndex = 4;
            this->label9->Text = this->tabPage5->Text;
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Location = System::Drawing::Point(460, 400);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(185, 30);
            this->label10->TabIndex = 4;
            this->label10->Text = this->tabPage6->Text;
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(920, 400);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(185, 30);
            this->label11->TabIndex = 4;
            this->label11->Text = this->tabPage7->Text;
            //
            // comboBox1
            //
            this->comboBox1->AutoSize = true;
            this->comboBox1->Location = System::Drawing::Point(1380, 420);
            this->comboBox1->Name = L"comboBox1";
            this->comboBox1->Size = System::Drawing::Size(185, 360);
            this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
            this->comboBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::combo1_KeyPress);
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1898, 1144);
            this->Controls->Add(this->tabControl1);
            this->Controls->Add(this->panel1);
            this->Name = L"MainForm";
            this->ShowIcon = false;
            this->ShowInTaskbar = false;
            this->Text = L"TableLab";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->tabPage2->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
            this->tabPage1->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->tabControl1->ResumeLayout(false);
            this->ResumeLayout(false);
        }
#pragma endregion

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string name = context.marshal_as<std::string>(textBox1->Text);
        std::string pol = context.marshal_as<std::string>(richTextBox1->Text);
        int cVar = 3;

        try {
            TPolinom polinom = ParsePolinom(pol, cVar);
            tableController->Insert(name, polinom);
            UpdateAllData();
        }
        catch (std::runtime_error e) {
            MessageBox::Show(gcnew String(e.what()));
        }

    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        std::string name = context.marshal_as<std::string>(textBox2->Text);
        try {
            this->richTextBox2->Text = gcnew String(tableController->Find(name)->ToString().c_str());
        }
        catch (std::runtime_error e) {
            MessageBox::Show(gcnew String(e.what()));
        }
    }

    private: System::Void tabControl1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        if (this->tabControl1->SelectedIndex != 0) {
            tableController->SelectActiveTable(context.marshal_as<std::string>(this->tabControl1->SelectedTab->Text));
            richTextBox2->Text = "";
            comboBox1->SelectedIndex = comboBox1->Items->IndexOf(this->tabControl1->SelectedTab->Text);
        }
    }

    private: System::Void dataGridView1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == Keys::Delete) {
            auto it = ((DataGridView^)sender)->SelectedRows->GetEnumerator();
            while (it->MoveNext())
            {
                auto row = (DataGridViewRow^)it->Current;
                auto rowIt = row->Cells->GetEnumerator();
                rowIt->MoveNext();
                std::string name = context.marshal_as<std::string>(((DataGridViewCell^)rowIt->Current)->Value->ToString());

                try{
                    tableController->Remove(name);
                }
                catch (std::runtime_error) {
                    ;
                }
            }
            UpdateAllData();
        }
    }

    private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        String^ selectedState = this->comboBox1->SelectedItem->ToString();
        tableController->SelectActiveTable(context.marshal_as<std::string>(selectedState));
    }

    private: System::Void combo1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e )
    {
        e->KeyChar = (char)Keys::None;
    }

    private: String^ RuStr(String^ str) {
        return utf8->GetString(win1251->GetBytes(str));
    }

    private: void UpdateData(DataGridView^ view, std::string nameOfTable) {
        view->Rows->Clear();

        std::string lastActiveTable = tableController->GetActiveName();
        tableController->SelectActiveTable(nameOfTable);

        if (tableController->GetRecCount() != 0)
            for (tableController->Reset(); !tableController->IsTabEnded(); tableController->GoNext()) {
                array<String^>^ values = gcnew array<String^>(2);
                values[0] = gcnew String(this->tableController->GetKey().c_str());
                values[1] = gcnew String(this->tableController->GetValuePtr()->ToString().c_str());
                view->Rows->Add(values);
            }

        tableController->SelectActiveTable(lastActiveTable);
    } 

    private: void UpdateAllData(void) {
        for (int i = 0; i < VIEW_SIZE; i++) {
            if (dataViews[i] == nullptr)
                return;

            std::string tableName = context.marshal_as<std::string>(dataViews[i]->Item1);
            UpdateData(dataViews[i]->Item2, tableName);
        }
    }

    private: TPolinom ParsePolinom(std::string pol, int cVar) {
        std::string word;
        std::smatch match, match1;
        VectorTable<std::string, TPolinom> tmpTable;

        std::stringstream ss(pol);

        // - Анализ всех введенных мономов
        // - Добавление мономов в таблицу временных имен
        // - Замена в входной стороке монома на временное имя
        while (ss >> word) {
            if (std::regex_match(word, std::regex("-?[\\d\\.,]+(\\*x\\d(\\^\\d)?)*"))) {
                std::regex_search(word, match, std::regex("^-?[\\d\\.,]+"));
                double coeff = std::stod(match.str());

                int* powers = new int[cVar] {};

                std::regex re("x(\\d)\\^?(\\d)?");
                for (std::sregex_iterator i = std::sregex_iterator(word.begin(), word.end(), re);
                    i != std::sregex_iterator(); ++i)
                {
                    match = *i;
                    int index = std::stoi(match[1]);
                    if (index >= cVar)
                        throw std::runtime_error("Wrong value of count varibles");

                    if (match.size() == 3)
                        powers[index] = std::stoi(match[2]);
                    else
                        powers[index] = 1;
                }

                TMonom monom(coeff, cVar, powers);
                TPolinom tmp(cVar);
                tmp.AddMonom(monom);

                std::string name = "_tmp" + std::to_string(tmpTable.GetDataCount());
                std::regex_search(pol, match1, std::regex("\\b-?[\\d\\.,]+(\\*x\\d(\\^\\d)?)*"));
                pol.replace(match1.position(), word.size(), name);

                tmpTable.Insert(name, tmp);
            }
        }

        // Проверка выражения на правильность
        TArithmeticExpression* expr;
        try {
            expr = new TArithmeticExpression(pol);
        }
        catch (std::logic_error e) {
            MessageBox::Show(gcnew String(e.what()));
        }

        TStack<TPolinom*> st(pol.size());
        TPolinom *leftOperand, *rightOperand;

        ss = std::stringstream(expr->GetPostfix());
        while (ss >> word)
        {
            // Обработка операций
            if (std::regex_match(word, std::regex("[\\+\\-\\/\\*\\^]"))) {
                TPolinom *res = new TPolinom(cVar);
                rightOperand = st.TopView();
                st.Pop();
                leftOperand = st.TopView();
                st.Pop();

                if (word == "+") *res = *leftOperand + *rightOperand;
                if (word == "-") *res = *leftOperand - *rightOperand;
                if (word == "*") *res = *leftOperand * *rightOperand;
                //if (word == "/") {
                //    if (rightOperand.ToString() == "0")
                //        throw std::logic_error("Divition by zero");
                //    res = leftOperand / rightOperand;
                //}
                st.Push(res);
            }
            // Обработка констант
            else if (std::regex_search(word, match, std::regex("^-?[\\d\\.,]+"))) {
                double coeff = std::stod(match.str());

                TMonom monom(coeff, cVar, new int[cVar]{});
                TPolinom *tmp = new TPolinom(cVar);
                tmp->AddMonom(monom);

                st.Push(tmp);
            }
            // Всё остальное считаем именем собственным
            else {
                try {
                    TPolinom* tmp;

                    // Запрос имен в временной таблице - приоритетный
                    try {
                        tmp = tmpTable.Find(word);
                    }
                    catch (std::exception) {
                        tmp = tableController->Find(word);
                    }

                    st.Push(tmp);
                }
                catch (std::runtime_error e) {
                    MessageBox::Show(gcnew String(e.what()));
                }
            }
        }

        return *st.TopView();
    }

};
}
