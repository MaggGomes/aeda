#include "OLZ.h"

OLZ::OLZ(){
	vector <Utilizador> usertemp;
	utilizadores = usertemp;
	vector <Anuncio * >  anunctemp;
	anuncios = anunctemp;
	userLogado = false;
}

OLZ::~OLZ(){
	
	for (unsigned int i = 0; i < anuncios.size(); i++){
		delete anuncios[i];
	}
}

vector<Utilizador> OLZ::getUtilizadores() const{
	return utilizadores;
}

vector<Anuncio *> OLZ::getAnuncios() const{
	return anuncios;
}

void OLZ::addUtilizador(Utilizador user){
	utilizadores.push_back(user);
}

void OLZ::addAnuncio(Anuncio * anunc){
	anuncios.push_back(anunc);
}

string OLZ::registarNome() {

	string nomeTemp;
	clrscr();
	impressaoTitulo();

	cout << ">> NICKNAME DE UTILIZADOR (entre 3 e 12 caracteres): ";
	getline(cin, nomeTemp);

	try{
		if (cin.fail() || nomeTemp.length() < 3 || nomeTemp.length() > 12)
			throw nomeTemp;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Nickname invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);	
		registarNome();
	}
		
	return nomeTemp;
}

bool OLZ::setVisNome() {

	string vis;

	clrscr();
	impressaoTitulo();

	cout << ">> DESEJA QUE O SEU NOME FIQUE VISIVEL? (<S>im / <N>ao): ";
	getline(cin, vis);

	try{
		if (cin.fail() || vis.length() != 1 )
			throw vis;
		if (vis == "s" || vis == "S")
			return true;
		if (vis == "n" || vis == "N")
			return false;

		throw vis;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Opcao invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		setVisNome();
	}

	return true;
}

string OLZ::registarEmail(){

	string emailTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> E-MAIL: ";
	getline(cin, emailTemp);

	try{
		if (cin.fail() || !validaEmail(emailTemp) || existeEmail(emailTemp))			//Caso o cin falhe, ou o mail nao seja válido ou já exista
			throw emailTemp;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: E-mail invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarEmail();
	}

	return emailTemp;
}

bool OLZ::setVisEmail() {
	return true;
}

bool OLZ::validaEmail(string mail)
{
	bool oneat = false;

	for (unsigned int i = 0; i < mail.size(); i++)
	{
		if (oneat == true && mail[i] == '@')				//Se ler mais que um @
			return false;
		else if (oneat == false && mail[i] == '@')			//Ao ler um @, faz set ao oneat
			oneat = true;
	}

	for (unsigned int i = 0; i < mail.size(); i++)
	{
		if (mail[i] == '.')			//Ao ler um '.' retorna true
			return true;
	}

	return false;
}

bool OLZ::existeEmail(string mail)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (mail == utilizadores[i].getEmail())
			return true;
	}

	return false;
}

int OLZ::registarTelefone(){

	int tlfTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> TELEFONE (9 digitos): ";
	cin >> tlfTemp;
	cin.ignore(100, '\n');

	try{
		if (cin.fail() || tlfTemp < 900000000 || tlfTemp > 999999999 || existeTelefone(tlfTemp))
			throw tlfTemp;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Telefone invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(800);
		registarTelefone();
	}
	
	return tlfTemp;
}

bool OLZ::setVisTelefone(){

	string vis;

	clrscr();
	impressaoTitulo();

	cout << ">> DESEJA QUE O SEU TELEFONE FIQUE VISIVEL? (<S>im / <N>ao): ";
	getline(cin, vis);
	

	try{
		if (cin.fail() || vis.length() != 1)
			throw vis;
		if (vis == "s" || vis == "S")
			return true;
		if (vis == "n" || vis == "N")
			return false;

		throw vis;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Opcao invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		setVisTelefone();
	}

	return true;
}

bool OLZ::existeTelefone(int tele)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (tele == utilizadores[i].getTelefone())
			return true;
	}

	return false;
}

Localizacao OLZ::registarLoc(){

	string fregTemp = registarFreg();
	string concTemp = registarConc();
	string distTemp = registarDistr();

	Localizacao temp(fregTemp, concTemp, distTemp);
	return temp;
}

bool OLZ::validarLocal(string local)
{
	for (unsigned int i = 0; i < local.size(); i++)
	{
		if (local[i] < 'A' || local[i] > 'z' || (local[i] < 'a' && local[i] > 'Z'))
			return false;
	}

	return true;
}

string OLZ::registarFreg()
{
	string fregTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> FREGUESIA ONDE MORA :";
	getline(cin, fregTemp);

	try
	{
		if (cin.fail() || !validarLocal(fregTemp))
			throw fregTemp;
	}
	catch(...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Freguesia invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarFreg();
	}

	return fregTemp;
}

string OLZ::registarConc()
{
	string concTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> CONCELHO ONDE MORA :";
	getline(cin, concTemp);

	try
	{
		if (cin.fail() || !validarLocal(concTemp))
			throw concTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Concelho invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarFreg();
	}

	return concTemp;
}

string OLZ::registarDistr()
{
	string distrTemp;

	clrscr();
	impressaoTitulo();

	cout << ">>  DISTRITO ONDE MORA :";
	getline(cin, distrTemp);

	try
	{
		if (cin.fail() || !validarLocal(distrTemp))
			throw distrTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Distrito invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(800);
		registarFreg();
	}

	return distrTemp;
}

string OLZ::setPass(){

	string passTemp;

	clrscr();
	impressaoTitulo();

	cout << " >> PASSWORD (Entre 6 e 12 caracteres): ";
	getline(cin, passTemp);

	try
	{
		if (cin.fail() || passTemp.size() < 6 || passTemp.size() > 12 || !validarPassword(passTemp))
			throw passTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Password invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		setPass();
	}

	return passTemp;
}

bool OLZ::validarPassword(string pass)
{
	for (unsigned int i = 0; i < pass.size(); i++)
	{
		if (pass[i] == ' ')
			return false;
	}

	return true;
}

void OLZ::registar() {

	string nomeTemp = registarNome();
	bool vis_nomeTemp = setVisNome();

	string emailTemp = registarEmail();
	bool vis_emailTemp = setVisEmail();

	string passTemp = setPass();

	int tlfTemp = registarTelefone();
	bool vis_telefoneTemp = setVisTelefone();

	Localizacao locTemp = registarLoc();	

	Utilizador userTemp(nomeTemp, emailTemp, tlfTemp, locTemp, passTemp);
	userTemp.setVisNome(vis_nomeTemp);
	userTemp.setVisEmail(vis_emailTemp);	
	userTemp.setVisTelefone(vis_telefoneTemp);
	utilizadores.push_back(userTemp);

	userLogado = true;
	userOnline = emailTemp;
	createMenuLogado();
}

void OLZ::logar(){
	
	string emailTemp, nomeTemp;
	string passTemp = "";
	int i = 0;
	bool validaEmail = false;
	bool validaPass = false;

	clrscr();
	impressaoTitulo();

	cout << ">> E-MAIL DE UTILIZADOR: ";
	getline(cin, emailTemp);
	
	// Verifica a existência do email

	try{
		if (cin.fail())
			throw emailTemp;

		for (unsigned int i = 0; i < utilizadores.size(); i++){
			if (utilizadores[i].getEmail() == emailTemp){
				validaEmail = true;
				nomeTemp = utilizadores[i].getNome();
				break;
			}
		}

		if (!validaEmail)
			throw emailTemp;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: E-mail de registo nao encontrado! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		logar();
	}

	while (i < 3 && !validaPass){ // Verifica se a password está correta; O utilizador tem 3 tentativas para efetuar o login
		passTemp = "";
		int tentativas = 3 - i;
		clrscr();
		impressaoTitulo();

		if (i == 0){
			setcolor(10, 0);
			cout << ":: AVISO: Tem " << tentativas << " tentativas restante(s)." << endl << endl;
			setcolor(7, 0);
		}

		if (i == 1){
			setcolor(14, 0);
			cout << ":: AVISO: Tem " << tentativas << " tentativas restante(s)." << endl << endl;
			setcolor(7, 0);
		}
		if (i == 2){
			setcolor(4, 0);
			cout << ":: AVISO: Tem " << tentativas << " tentativas restante(s)." << endl << endl;
			setcolor(7, 0);
		}

		cout << ">> PASSWORD DE UTILIZADOR: ";
		char ch;
		
		while ((ch = _getch()) != 13){

			if (ch == 8){
				if (passTemp.length() != 0){
					cout << "\b \b";
					passTemp.resize(passTemp.length() - 1);
				}
				
			}
			else if (ch == 0 || ch == 224) 
			{

				_getch(); 
				continue;
			}
			else{
				passTemp += ch;
				cout << '*';
			}
		}

		cout << endl;

		try{
			if (passTemp.length() < 6 || passTemp.length() > 12)
				throw passTemp;

			for (unsigned int i = 0; i < utilizadores.size(); i++){
				if (utilizadores[i].getEmail() == emailTemp){
					if (utilizadores[i].getPass() == passTemp)
						validaPass = true;
					break;
				}
			}

			if (!validaPass)
				throw passTemp;
		}
		catch (...){
			clean_buffer();
			setcolor(4, 0);
			cout << ":: ERRO: Password invalida! Tente novamente." << endl << endl;
			setcolor(7, 0);
			Sleep(1000);
		}

		i++;
	}

	if (!validaPass){
		setcolor(4, 0);
		cout << ":: ERRO: Falhou login! Voltando ao Menu Iniciar..." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuInicial();
	}
	
	clrscr();
	impressaoTitulo();
	setcolor(10, 0);
	cout << endl << endl << setw(40) <<":: BENVINDO "<< nomeTemp<<" !!!" << endl << endl;
	setcolor(7, 0);
	Sleep(2000);

	userLogado = true;
	userOnline = emailTemp;
	createMenuLogado();
}
// FALTA IMPLEMENTAR

void OLZ::criaAnuncioCompra(){

	Utilizador * userTemp;
	clrscr();
	impressaoTitulo();

	try
	{
		userTemp = pesquisaEmail(userOnline);
		string titTemp = registarTitulo();

		string catTemp = registarCategoria();

		string descrTemp = registarDescricao();

		vector<string> imgTemp = registarImagens();

		Data DatacriacaoTemp;

		float precoTemp = registarPreco();

		bool possivelNegociarTemp = registarPossivelNegociar();

		vector<Anuncio *> trocaTemp;

		Anuncio * temp = new AnuncioCompra(userTemp, titTemp, catTemp, descrTemp, possivelNegociarTemp, precoTemp, trocaTemp);

		anuncios.push_back(temp);
	}
	catch (EmailNaoEncontrado)					//Caso haja um problema na base de dados
	{
		clrscr();
		impressaoTitulo();
		cout << "Houve um problema com a base de dados. O seu email não está registado. Registe-se novamente por favor" << endl;
		userLogado = false;
		userOnline = "";
		createMenuInicial();
	}	
	return;	
}

string OLZ::registarEstado()
{
	string estadoTemp;

	clrscr();
	impressaoTitulo();
	clean_buffer();

	cout << ">> ESTADO DO PRODUTO (novo/usado como novo/funcional/para pecas) :";
	getline(cin, estadoTemp);

	try
	{
		if (!(estadoTemp == "novo" || estadoTemp == "Novo" || estadoTemp == "usado como novo" || estadoTemp == "usado" || estadoTemp == "Usado como novo" || estadoTemp == "funcional" || estadoTemp == "Funcional" || estadoTemp == "para pecas" || estadoTemp == "Para pecas"))
			throw estadoTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Descricao com demasiados caracteres! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarEstado();
	}

	return estadoTemp;
}

void OLZ::criaAnuncioVenda()
{
	Utilizador * userTemp;
	clrscr();
	impressaoTitulo();

	try
	{
		userTemp = pesquisaEmail(userOnline);
		string titTemp = registarTitulo();

		string catTemp = registarCategoria();

		string descrTemp = registarDescricao();

		vector<string> imgTemp = registarImagens();

		Data DatacriacaoTemp;

		float precoTemp = registarPreco();

		bool possivelNegociarTemp = registarPossivelNegociar();

		string estadoTemp = registarEstado();

		Anuncio * temp = new AnuncioVenda(userTemp, titTemp, catTemp, descrTemp, possivelNegociarTemp, precoTemp, estadoTemp);

		anuncios.push_back(temp);
	}
	catch (EmailNaoEncontrado)					//Caso haja um problema na base de dados
	{
		clrscr();
		impressaoTitulo();
		cout << "Houve um problema com a base de dados. O seu email não está registado. Registe-se novamente por favor" << endl;
		userLogado = false;
		userOnline = "";
		createMenuInicial();
	}

	return;
}
void OLZ::setuserLogado(bool &log){
	userLogado = log;
}

bool OLZ::getuserLogado() const{
	return userLogado;
}

void OLZ::createMenuInicial(){
	string Menu[4] = { "<<   VISITANTE        >>", "<<   UTILIZADOR       >>", "<<   ADMINISTRADOR    >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<< MENU INICIAL >>>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					createMenuVisitante();
					break;
				case 1:
					validade = false;
					createMenuUser();
					break;
				case 2:
					validade = false;
					createMenuAdmin();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuVisitante(){
	string Menu[4] = { "<<   MENU INICIAL     >>", "<<   REGISTAR         >>", "<<   PESQUISAR        >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<  VISITANTE   >>>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					createMenuInicial();
					break;
				case 1:
					validade = false;
					registar();
					break;
				case 2:
					validade = false;
					createMenuPesquisaVis();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuUser(){
	string Menu[3] = { "<<   MENU INICIAL     >>", "<<   LOGIN            >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<    LOGIN     >>>>>" << endl << endl;

		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					createMenuInicial();
					break;
				case 1:
					validade = false;
					logar();
					break;
				case 2:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuLogado(){
	string Menu[6] = { "<<   MENU INICIAR     >>", "<<   CRIAR ANUNCIO    >>", "<<   MEUS ANUNCIOS    >>", "<<   PESQUISA ANUNCIO >>", "<<   VER CONTATOS     >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<  UTILIZADOR  >>>>>" << endl << endl;

		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 6)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 5;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					userLogado = false;
					createMenuInicial();
					break;
				case 1:
					validade = false;
					createMenuCriaAnuncio();
					break;
				case 2:
					createMenuAnuncios();
				case 3:
					createMenuPesquisaUser();
				case 4:
					exiting();// FALTA IMPLEMENTAR
				case 5:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuCriaAnuncio(){
	string Menu[4] = { "<<   MENU USER        >>", "<<   ANUNCIO VENDA    >>", "<<   ANUNCIO COMPRA   >>", "<<   SAIR             >>"  };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<< TIPO ANUNCIO >>>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					userLogado = true;
					createMenuLogado();
					break;
				case 1:
					validade = false;
					criaAnuncioVenda();
					createMenuLogado();
					break;
				case 2:
					validade = false;
					criaAnuncioCompra();
					createMenuLogado();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuAnuncios(){
	string Menu[5] = { "<<   MENU USER        >>", "<<   VER TODOS        >>", "<<   MAIS RECENTE     >>", "<<   MAIS CLICKS      >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<   ANUNCIOS   >>>>>" << endl << endl;

		for (int i = 0; i < 5; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 5)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 4;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					createMenuLogado();
					break;
				case 1:
					validade = false;
					MostraAnunciosUser(userOnline);
					break;
				case 2:
					AnuncUserRec();
					createMenuAnuncios();
				case 3:
					AnuncUserClicks();
					createMenuAnuncios();
				case 4:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::AnuncUserClicks(){

	clrscr();
	impressaoTitulo();
	vector <Anuncio * > temp;

	for (unsigned int i = 0; i < anuncios.size(); i++){
		if (anuncios[i]->getAnunciante()->getEmail() == userOnline)
			temp.push_back(anuncios[i]);
	}

	if (temp.size() == 0){
		setcolor(4, 0);
		cout << ":: ERRO: Nao possui qualquer anuncio ainda!" << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuAnuncios();
	}

	if (temp.size() == 1){
		temp[0]->visAnuncio();
		cout << endl;
		system("pause");
		createMenuAnuncios();
	}

	int id = 0;

	for (unsigned int i = 0; i < temp.size() - 1; i++){
		if (temp[i]->getClicks() >= temp[i + 1]->getClicks())
			id = i;
		else
			id = i + 1;
	}


	temp[id]->visAnuncio();
	cout << endl;
	system("pause");
	createMenuAnuncios();
}

void OLZ::AnuncUserRec(){
	
	clrscr();
	impressaoTitulo();
	vector <Anuncio * > temp;

	for (unsigned int i = 0; i < anuncios.size(); i++){
		if (anuncios[i]->getAnunciante()->getEmail() == userOnline)
			temp.push_back(anuncios[i]);
	}

	if (temp.size() == 0){
		setcolor(4, 0);
		cout << ":: ERRO: Nao possui qualquer anuncio ainda!" << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuAnuncios();
	}

	if (temp.size() == 1){
		temp[0]->visAnuncio();
		cout << endl;
		system("pause");
		createMenuAnuncios();
	}
	
	int id = 0;

	for (unsigned int i = 0; i < temp.size()-1; i++){
		if (temp[i]->getDataCriacao() < temp[i + 1]->getDataCriacao())
			id = i;
		else
			id = i + 1;
		}
	

	temp[id]->visAnuncio();
	cout << endl;
	system("pause");
	createMenuAnuncios();
}

void OLZ::createMenuAdmin(){
	string Menu[4] = { "<<   MENU INICIAL     >>", "<<   GERIR USERS      >>", "<<   GERIR ANUNCIOS   >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<    ADMIN     >>>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					createMenuInicial();
					break;
				case 1:
					validade = false;
					createMenuGerirUsers();
					break;
				case 2:
					validade = false;
					createMenuGerirAnuncios();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::apagarUser(){
	
	string emailTemp;
	bool validaEmail = false;

	adminMostraUsers();
	cout << endl;
	cout << ">> E-MAIL DE UTILIZADOR: ";
	getline(cin, emailTemp);

	// Verifica a existência do email

	try{
		if (cin.fail())
			throw emailTemp;

		int x = searchUtilizador(emailTemp);
		if (x == -1)
			throw emailTemp;

		Utilizador dUt = utilizadores[x];
		
		utilizadores.erase(utilizadores.begin()+x);
		
		for (unsigned int j = 0; j < anuncios.size(); j++){
			if (anuncios[j]->getAnunciante()->getEmail() == emailTemp){
				anuncios.erase(anuncios.begin() + j);
				j--;	
			}
		}	

	}catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: E-mail de registo nao encontrado! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuGerirUsers();
	}

	createMenuGerirUsers();
}

void OLZ::apagarAnuncio()
{
	int anunTemp;
	bool validaTemp = false;

	clrscr();
	impressaoTitulo();
	for (int i = 0; i < anuncios.size(); i++)
	{
		setcolor(4, 0);
		cout << anuncios[i]->getID() << " - " << anuncios[i]->getTitulo() << endl;
		setcolor(7, 0);
	}
		
	cout << endl;
	cout << ">> ID DO ANUNCIO: ";
	cin >> anunTemp;

	
	try{
		if (cin.fail())
			throw anunTemp;

		int x = searchAnuncio(anunTemp);
		if (x == -1)
			throw anunTemp;

		anuncios.erase(anuncios.begin() + x);

	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Anuncio nao encontrado! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuGerirAnuncios();
	}

	createMenuGerirAnuncios();
}

void OLZ::createMenuGerirUsers(){
	string Menu[4] = { "<<   MENU ADMIN       >>", "<<   VER USERS        >>", "<<   APAGAR USER      >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<< GERIR USERS  >>>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					saveData();
					createMenuAdmin();
					break;
				case 1:
					validade = false;
					adminMostraUsers();
					break;
				case 2:
					validade = false;
					apagarUser();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuGerirAnuncios(){
	string Menu[4] = { "<<   MENU ADMIN       >>", "<<   VER ANUNCIOS     >>", "<<   APAGAR ANUNCIO   >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<< GERIR ANUNCIOS >>>>" << endl << endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					saveData();
					createMenuAdmin();
					break;
				case 1:
					validade = false;
					adminMostraAnuncios();
					break;
				case 2:
					validade = false;
					apagarAnuncio();
					break;
				case 3:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::pesquisaCat(const string &cat){
	clrscr();
	impressaoTitulo();
	vector <Anuncio * > temp;

	for (unsigned int i = 0; i < anuncios.size(); i++){
		if (anuncios[i]->getAnunciante()->getEmail() != userOnline){
			if (anuncios[i]->getCategoria() ==cat)
				temp.push_back(anuncios[i]);
		}			
	}

	if (temp.size() == 0){
		setcolor(4, 0);
		cout << ":: ERRO: Nao existe qualquer anuncio de outra anunciante da categoria que procura!" << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		createMenuPesquisaVis();
	}

	if (temp.size() == 1){
		temp[0]->visAnuncio();
		cout << endl;
		system("pause");
		createMenuPesquisaVis();
	}


	for (unsigned int i = 0; i < temp.size() - 1; i++){
		temp[i]->visAnuncio();
	}
	
	cout << endl;
	system("pause");
	createMenuPesquisaVis();
}

void OLZ::createMenuPesquisaVis(){
	string Menu[5] = { "<<   MENU INICIAR     >>", "<<   CATEGORIA        >>", "<<   PALAVRA-CHAVE    >>", "<<   PRECO            >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<   PESQUISA   >>>>>" << endl << endl;

		for (int i = 0; i < 5; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 5)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 4;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					userLogado = false;
					saveData();
					createMenuInicial();
					break;
				case 1:
				{
					string cat;
					clrscr();
					impressaoTitulo();
					cout << ">> CATEGORIA DO ANUNCIO: ";
					getline(cin, cat);
					pesquisaCat(cat);
				}
				case 2:
				{
					string cat;
					clrscr();
					impressaoTitulo();
					cout << ">> PALAVRA CHAVE: ";
					getline(cin, cat);
					pesquisaCat(cat);
				}
				case 3:
					float p;
					clrscr();
					impressaoTitulo();
					cout << ">> PRECO: ";
					cin >> p;
					cin.ignore(1000, '\n');
					pesquisaPreco(p);
					system("Pause");
					createMenuInicial();
					exiting();  			
				case 4:
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::createMenuPesquisaUser(){
	string Menu[5] = { "<<   MENU USER        >>", "<<   CATEGORIA        >>", "<<   PALAVRA-CHAVE    >>", "<<   PRECO            >>", "<<   SAIR             >>" };
	bool validade = true;
	int pointer = 0;

	while (validade)
	{
		clrscr();
		impressaoTitulo();
		setcolor(11, 0);
		cout << setw(51) << "<<<<<   PESQUISA   >>>>>" << endl << endl;

		for (int i = 0; i < 5; ++i)
		{
			if (i == pointer)
			{
				cout << "                           ";
				setcolor(3, 1);
				cout << Menu[i] << endl << endl;
			}
			else
			{
				setcolor(3, 0);
				cout << setw(51) << Menu[i] << endl << endl;
			}
		}
		setcolor(7, 0);

		while (validade)
		{
			int ch = _getch();

			if (ch == 0 || ch == 224)
				ch = 256 + _getch();

			if (ch == ARROW_DOWN) {
				Beep(250, 160);
				pointer += 1;
				if (pointer == 5)
				{
					pointer = 0;
				}
				break;
			}

			if (ch == ARROW_UP){
				Beep(250, 160);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 4;
				}
				break;
			}

			if (ch == '\r')
			{
				setcolor(7, 0);
				Beep(200, 160);

				switch (pointer)
				{
				case 0:
					validade = false;
					saveData();
					createMenuLogado();
					break;
				case 1:
					exiting(); // FALTA IMPLEMENTAR
				case 2:
					exiting(); // FALTA IMPLEMENTAR
				case 3:
					float p;
					clrscr();
					impressaoTitulo();
					cout << ">> PRECO: ";
					cin >> p;
					cin.ignore(1000, '\n');
					pesquisaPreco(p);
					system("Pause");
					createMenuPesquisaUser();
					exiting();
				case 4:	
					saveData();
					exiting();
				}
			}
		}
	}
}

void OLZ::saveData()
{
	ofstream utFile; // variavel que vai conter o vector de Utilizadores
	ofstream anFile; // variavel que vai conter o vector de Anuncios
	ofstream ctFile; // variavel que vai conter o vector de Contatos

	remove("utilizadores.csv");	
	utFile.open("utilizadores.csv");
	
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		Utilizador temp = utilizadores[i];
		utFile << temp.getNome() << ";" << temp.getEmail() << ";" << temp.getTelefone() << ";" << temp.getLocalizacao().getFreguesia() << ";" << temp.getLocalizacao().getConcelho() << ";" << temp.getLocalizacao().getDistrito() << ";" << temp.getPass() << ";";

		utFile << temp.getMensRec().size() << ";";
		for (unsigned int j = 0; j < temp.getMensRec().size(); j++)
		{
			utFile << temp.getMensRec()[j] << ";";
		}

		utFile << temp.getMensEnv().size() << ";";
		for (unsigned int j = 0; j < temp.getMensEnv().size(); j++)
		{
			utFile << temp.getMensEnv()[j] << ";";
		}

		if (i != utilizadores.size() - 1)
			utFile << temp.getVisNome() << ";" << temp.getVisEmail() << ";" << temp.getVisTelefone() << "\n";
		else 
			utFile << temp.getVisNome() << ";" << temp.getVisEmail() << ";" << temp.getVisTelefone();
	}

	utFile.close();

	remove("anuncios.csv");
	anFile.open("anuncios.csv");

	for (unsigned int i = 0; i < anuncios.size(); i++)
	{
		Anuncio * temp = anuncios[i];
		anFile << temp->getAnunciante()->getEmail() << ";" << temp->getTitulo() << ";" << temp->getCategoria() << ";" << temp->getDescricao() << ";" << temp->getID() << ";";
		
		anFile << temp->getImagens().size() << ";";
		for (unsigned int j = 0; j < temp->getImagens().size(); j++)
		{
			anFile << temp->getImagens()[j] << ";";
		}

		anFile << temp->getDataCriacao().getDia() << ";" << temp->getDataCriacao().getMes() << ";" << temp->getDataCriacao().getAno() << ";" << temp->getNegociar() << ";" << temp->getClicks() << ";" << temp->getPreco() << ";";
		
		if (i != anuncios.size() - 1)
		{
			if (temp->isVenda())
			{
				anFile << true << ";";
				anFile << temp->getEstado() << "\n";
			}
			else
			{
				anFile << false << ";";

			
				anFile << temp->getTroca().size();
				if (temp->getTroca().size() == 0)
					anFile << "\n";
				else
					for (size_t i = 0; i < temp->getTroca().size(); i++)
					{
						if (i == temp->getTroca().size() - 1)
							anFile << temp->getTroca()[i]->getID() << "\n";
						else
							anFile << temp->getTroca()[i]->getID() << ";";
					}

				for (size_t i = 0; i < temp->getTroca().size(); i++)
				{
					if (i == temp->getTroca().size() - 1)
						anFile << temp->getTroca()[i]->getID() << "\n";
					else
						anFile << temp->getTroca()[i]->getID() << ";";
				}

			}
		}
		else
		{
			if (temp->isVenda())
			{
				anFile << true << ";";
				anFile << temp->getEstado();
			}
			else
			{
				anFile << false << ";";
				for (size_t i = 0; i < temp->getTroca().size(); i++)
				{
					if (i == temp->getTroca().size() - 1)
						anFile << temp->getTroca()[i]->getID();
					else
						anFile << temp->getTroca()[i]->getID() << ";";
				}
			}
		}
	}

	anFile.close();

	remove("contatos.csv");
	ctFile.open("contatos.csv");

	for (unsigned int i = 0; i < contatos.size(); i++)
	{
		Contato temp = contatos[i];
		
		ctFile << temp.getID() << ";" << temp.getAnuncio()->getID() << ";" << temp.getMensagem() << ";" << temp.getContacto() << ";";

		if (i == contatos.size() - 1)
			ctFile << temp.getRemetente();
		else
			ctFile << temp.getRemetente() << "\n";
	}

	ctFile.close();
}

void OLZ::loadData()
{
	
	ifstream utFile; // variavel que vai conter o ficheiro de Utilizadores
	ifstream anFile; // variavel que vai conter o ficheiro de Anuncios
	ifstream ctFile; // variavel que vai conter o ficheiro de Contatos
		
	utFile.open("utilizadores.csv");

	string line;
	
	while (getline(utFile, line)){
		istringstream ss(line);

		while (ss.good()) {

	int i = 0;
	string tNome;
	getline(ss, tNome, ';');	
	string tEmail;
	getline(ss, tEmail, ';');


	string stNr;
	getline(ss, stNr, ';');
	int tNr = atoi(stNr.c_str());

	string tFreg;
	getline(ss, tFreg, ';');

	string tConc;
	getline(ss, tConc, ';');

	string tDist;
	getline(ss, tDist, ';');

	Localizacao tLoc(tFreg, tConc, tDist);

	string tPass;
	getline(ss, tPass, ';');

	Utilizador tUti(tNome, tEmail, tNr, tLoc, tPass);

	string siMR;
	getline(ss, siMR, ';');
	int iMR = atoi(siMR.c_str());

	vector<int> tMR;
	for (int i = 0; i < iMR; i++)
	{
		string abc;
		getline(ss, abc, ';');
		int x = atoi(abc.c_str());
		tMR.push_back(x);
	}

	tUti.setMR(tMR);

	string siME;
	getline(ss, siME, ';');
	int iME = atoi(siME.c_str());

	vector<int> tME;
	for (int i = 0; i < iME; i++)
	{
		string abc;
		getline(ss, abc, ';');
		int x = atoi(abc.c_str());
		tME.push_back(x);
	}


	tUti.setME(tME);

	string stVisN;
	getline(ss, stVisN, ';');
	int itVisN = atoi(stVisN.c_str());
	bool tVisN = itVisN;

	tUti.setVisNome(tVisN);

	string stVisE;
	getline(ss, stVisE, ';');
	int itVisE = atoi(stVisE.c_str());
	bool tVisE = itVisE;


	tUti.setVisEmail(tVisE);

	string stVisT;
	getline(ss, stVisT, ';');
	int itVisT = atoi(stVisT.c_str());
	bool tVisT = itVisT;

	tUti.setVisTelefone(tVisT);

	utilizadores.push_back(tUti);	
		}
	}	
		
	utFile.close();
	
	anFile.open("anuncios.csv");
	/*
	while (getline(anFile, line)){
		istringstream ss(line);
		
		while (ss.good()) {
			string tEmail;
			getline(ss, tEmail, ';');

			cout << tEmail << endl;

			int iAn = searchUtilizador(tEmail);

			Utilizador tAn = utilizadores[iAn];
			
			string tTit;
			getline(ss, tTit, ';');

			string tCat;
			getline(ss, tCat, ';');

			string tDes;
			getline(ss, tDes, ';');

			string stID;
			getline(ss, stID, ';');
			int tID = atoi(stID.c_str());

			string stIma;
			getline(ss, stIma, ';');
			int tIma = atoi(stIma.c_str());

			vector<string> viIma;

			for (int i = 0; i < tIma; i++)
			{
				string tABC;
				getline(ss, tABC, ';');
				viIma.push_back(tABC);
			}

			string stDia;
			getline(ss, stDia, ';');
			int tDia = atoi(stDia.c_str());

			string stMes;
			getline(ss, stMes, ';');
			int tMes = atoi(stMes.c_str());

			string stAno;
			getline(ss, stAno, ';');
			int tAno = atoi(stAno.c_str());

			Data tData(tDia, tMes, tAno);

			string stNeg;
			getline(ss, stNeg, ';');
			int itNeg = atoi(stNeg.c_str());
			bool tNeg = itNeg;

			cout << tNeg << endl;

			string stCl;
			getline(ss, stCl, ';');
			int tCl = atoi(stCl.c_str());

			string stPr;
			getline(ss, stPr, ';');
			int tPr = atof(stPr.c_str());

			string stVen;
			getline(ss, stVen, ';');
			int itVen = atoi(stVen.c_str());
			bool tVen = itVen;




	tUti.setVisEmail(tVisE);

	string stVisT;
	getline(ss, stVisT, ';');
	int itVisT = atoi(stVisT.c_str());
	bool tVisT = itVisT;

	tUti.setVisTelefone(tVisT);

	utilizadores.push_back(tUti);	
		}
	}	
		
	utFile.close();
	
	anFile.open("anuncios.csv");

	while (getline(anFile, line)){
		istringstream ss(line);
		
		while (ss.good()) {
			string tEmail;
			getline(ss, tEmail, ';');

			cout << tEmail << endl;

			int iAn = searchUtilizador(tEmail);

			Utilizador tAn = utilizadores[iAn];
			
			string tTit;
			getline(ss, tTit, ';');

			string tCat;
			getline(ss, tCat, ';');

			string tDes;
			getline(ss, tDes, ';');

			string stID;
			getline(ss, stID, ';');
			int tID = atoi(stID.c_str());

			string stIma;
			getline(ss, stIma, ';');
			int tIma = atoi(stIma.c_str());

			vector<string> viIma;

			for (int i = 0; i < tIma; i++)
			{
				string tABC;
				getline(ss, tABC, ';');
				viIma.push_back(tABC);
			}

			string stDia;
			getline(ss, stDia, ';');
			int tDia = atoi(stDia.c_str());

			string stMes;
			getline(ss, stMes, ';');
			int tMes = atoi(stMes.c_str());

			string stAno;
			getline(ss, stAno, ';');
			int tAno = atoi(stAno.c_str());

			Data tData(tDia, tMes, tAno);

			string stNeg;
			getline(ss, stNeg, ';');
			int itNeg = atoi(stNeg.c_str());
			bool tNeg = itNeg;

			cout << tNeg << endl;

			string stCl;
			getline(ss, stCl, ';');
			int tCl = atoi(stCl.c_str());

			string stPr;
			getline(ss, stPr, ';');
			int tPr = atof(stPr.c_str());

			string stVen;
			getline(ss, stVen, ';');
			int itVen = atoi(stVen.c_str());
			bool tVen = itVen;



			if (tVen)
			{
				string tEst;
				getline(ss, tEst, ';');
				Anuncio * anun = new AnuncioVenda(&tAn, tTit, tCat, tDes, tNeg, tPr, tEst);
				anun->setDataCriacao(tData);

				anun->setNum_clicks(tCl);

				anun->setImagens(viIma);


				anun->setId(tID);


				anun->setId(tID);

				anuncios.push_back(anun);
			}
			else
			{
				vector<Anuncio *> tTroca;

				string stTr;
				getline(ss, stTr, ';');
				int tTr = atof(stTr.c_str());

				for (int i = 0; i < tTr; i++)
				{
					string stAnI;
					getline(ss, stAnI, ';');
					int tAnI = atof(stAnI.c_str());
					int x = searchAnuncio(tAnI);
					tTroca.push_back(anuncios[x]);
				}
				Anuncio * anun = new AnuncioCompra(&tAn, tTit, tCat, tDes, tNeg, tPr, tTroca);

				anun->setDataCriacao(tData);

				anun->setNum_clicks(tCl);

				anun->setId(tID);
				
				anun->setImagens(viIma);

=======

				string stTr;
				getline(ss, stTr, ';');
				int tTr = atof(stTr.c_str());

				for (int i = 0; i < tTr; i++)
				{
					string stAnI;
					getline(ss, stAnI, ';');
					int tAnI = atof(stAnI.c_str());
					int x = searchAnuncio(tAnI);
					tTroca.push_back(anuncios[x]);
				}
				Anuncio * anun = new AnuncioCompra(&tAn, tTit, tCat, tDes, tNeg, tPr, tTroca);

				anun->setDataCriacao(tData);

				anun->setNum_clicks(tCl);
				anun->setId(tID);
				anun->setImagens(viIma);


				anuncios.push_back(anun);
			}
		}
	}

	
	
	anFile.close();


	cout << "finis" << endl;

	anFile.close();
	cout << "finis2" << endl;

	for (unsigned int i = 0; i < anuncios.size(); i++){
		anuncios[i]->visAnuncio();
	}


	/*
	ctFile.open("contatos.csv");
	while (!ctFile.eof())
	{
		string stID;
		getline(anFile, stID, ';');
		int tID = atof(stID.c_str());

		string stAnID;
		getline(anFile, stAnID, ';');
		int tAnID = atof(stAnID.c_str());

		int x = searchAnuncio(tAnID);

		string tMens;
		getline(anFile, tMens, ';');
		
		string tCont;
		getline(anFile, tCont, ';');

		string tRem;
		getline(anFile, tRem, ';');

		Contato tCt(anuncios[x], tRem, tMens, tCont);

		contatos.push_back(tCt);
	}
	ctFile.close();
	*/
}

Utilizador * OLZ::pesquisaEmail(string mail)
{
	for (unsigned int i = 0; i < utilizadores.size(); i++)
	{
		if (utilizadores[i].getEmail() == mail)
			return &utilizadores[i];
	}

	EmailNaoEncontrado m(mail);
	throw(m);
}

bool OLZ::validarTitulo(string tit)
{
	if (tit.size() < 1 || tit.size() > 30)
		return false;
	else
		return true;
}

string OLZ::registarTitulo()
{
	string titTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> TITULO DO ANUNCIO (menos de 30 caracteres): ";
	getline(cin, titTemp);

	try
	{
		if (cin.fail() || !validarTitulo(titTemp))
			throw titTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Titulo invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarTitulo();
	}

	return titTemp;
}

bool OLZ::validarCategoria(string cat)
{
	if (cat.size() < 1 || cat.size() > 15)
		return false;
	else
		return true;
}
string OLZ::registarCategoria()
{
	string catTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> CATEGORIA DO PRODUTO (menos de 15 caracteres): ";
	getline(cin, catTemp);

	try
	{
		if (cin.fail() || !validarCategoria(catTemp))
			throw catTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Titulo invalido! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarCategoria();
	}

	return catTemp;
}

string OLZ::registarDescricao()
{
	string descrTemp;

	clrscr();
	impressaoTitulo();

	cout << ">> DESCRICAO DO PRODUTO (menos de 1000 caracteres): ";
	getline(cin, descrTemp);

	try
	{
		if (cin.fail() || descrTemp.size() > 1000)
			throw descrTemp;
	}
	catch (...)
	{
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Descricao com demasiados caracteres! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarDescricao();
	}

	return descrTemp;
}
vector<string> OLZ::registarImagens()
{
	bool querImagens;
	char quer;

	bool valido = false;
	while (!valido)
	{
		clrscr();
		impressaoTitulo();
		cout << " >> DESEJA INSERIR IMAGENS NO SEU ANUNCIO? ((S)im/(N)ao): ";
		cin >> quer;
		cin.ignore(100, '\n');

		if (quer == 'S' || quer == 's')
		{
			querImagens = true;
			valido = true;
		}
		else if (quer == 'N' || quer == 'n')
		{
			querImagens = false;
			valido = true;
		}
		else
		{
			clean_buffer();
			setcolor(4, 0);
			cout << ":: ERRO: Comando invalido! Tente novamente." << endl << endl;
			setcolor(7, 0);
			Sleep(1000);
		}
	}

	vector<string> img;

	while (querImagens)
	{
		valido = false;
		bool erro = false;
		while (!valido)
		{
			if (!erro)
			{
				string img1;
				clean_buffer();
				cout << " >> INSIRA UMA IMAGEM: ";
				getline(cin, img1);
				img.push_back(img1);
				clean_buffer();
			}
			clrscr();
			impressaoTitulo();

			cout << endl << ">> QUER INSERIR MAIS IMAGENS? ((S)im/(N)ao): ";
			cin >> quer;
			if (quer == 'S' || quer == 's')
			{
				querImagens = true;
				valido = true;
				erro = false;
			}
			else if (quer == 'N' || quer == 'n')
			{
				querImagens = false;
				valido = true;
				erro = false;
			}
			else
			{
				erro = true;
				clean_buffer();
				setcolor(4, 0);
				cout << ":: ERRO: Comando invalido! Tente novamente." << endl << endl;
				setcolor(7, 0);
				Sleep(1000);
			}
		}
	}

	return img;
}

bool OLZ::registarPossivelNegociar()
{
	bool possivel = true;
	string vis;

	clrscr();
	impressaoTitulo();

	cout << ">> QUER PERMITIR A POSSIBILIDADE DE NEGOCIACAO DO PRECO? ((S)im/(N)ao): ";

	cin >> vis;

	try
	{

		cout << "fail" << endl;
		if (vis == "s" || vis == "S")
			return true;
		if (vis == "n" || vis == "N")
			return false;
		else
			throw vis;

	}
	catch (...){
		cin.clear();
		cin.ignore(1000, '\n');
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Opcao invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarPossivelNegociar();

	}
	
	return possivel;
}
float OLZ::registarPreco()
{
	float precoTemp;

	clrscr();
	impressaoTitulo();

	cout << ">>INSIRA O PRECO DESEJADO: ";
	cin >> precoTemp;
	cin.ignore(1000, '\n');
	cin.clear();
	try{
		if (cin.fail() || precoTemp <= 0)
			throw precoTemp;
	}
	catch (...){
		clean_buffer();
		setcolor(4, 0);
		cout << ":: ERRO: Opcao invalida! Tente novamente." << endl << endl;
		setcolor(7, 0);
		Sleep(1000);
		registarPreco();
	}

	return precoTemp;
}

vector<Anuncio *> OLZ::registarTroca()
{
	vector<Anuncio *> trocatmp;
	vector<Anuncio *> anunciosUser = searchAnuncioVenda(userOnline);
	string tit;

	while(true)
	{
		if(anunciosUser.size() == 0)
			return trocatmp;

		clrscr();
		impressaoTitulo();

		cout << ">> QUAIS ANUNCIOS E QUE QUER COLOCAR PARA TROCA? (escreva o titulo do anuncio): " << endl;
		cout << " (Mais nenhum)" << endl;
		for (int i = 0; i < anunciosUser.size(); i++)
		{	

			cout << anunciosUser[i]->titulo << endl;
		}
		cin >> tit;

		int posicaoVetor = searchTituloNoVetor(tit, anunciosUser);
		if (tit == "Nenhum" || tit == "nenhum" || tit == "Mais nenhum" || tit == "mais nenhum" || tit == "Mais Nenhum" || tit == "mais Nenhum")
		{
			return trocatmp;
		}
		else if ( posicaoVetor != -1)
		{
			trocatmp.push_back(anunciosUser[posicaoVetor]);
			anunciosUser.erase(anunciosUser.begin() + posicaoVetor);
		}
		else
		{
			clean_buffer();
			setcolor(4, 0);
			cout << ":: ERRO: Opcao invalida! Tente novamente." << endl << endl;
			setcolor(7, 0);
			Sleep(1000);
		}
	}

	
}

vector<Anuncio *> OLZ::searchAnuncioVenda(string mailutilizador)
{
	vector<Anuncio *> compraTemp;

	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->Anunciante->getEmail() == mailutilizador && anuncios[i]->isVenda())
			compraTemp.push_back(anuncios[i]);
	}

	return compraTemp;
}

int OLZ::searchTituloNoVetor(string t, vector<Anuncio *> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if(t == v[i]->getTitulo())
			return i;
	}

	return -1;
}

int OLZ::searchUtilizador(string emailUt)
{
	for (int i = 0; i < utilizadores.size(); i++)
	{
		if (utilizadores[i].getEmail() == emailUt)
			return i;
	}
	return -1;
}

int OLZ::searchAnuncio(int AnID)
{
	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->getID() == AnID)
			return i;
	}
	return -1;
}

void OLZ::adminMostraUsers()
{
	clrscr();
	impressaoTitulo();
	for (int i = 0; i < utilizadores.size(); i++)
	{
		setcolor(4, 0);
		cout << "NOME: " << utilizadores[i].getNome() << " EMAIL: " << utilizadores[i].getEmail() << endl;
		setcolor(7, 0);
	}

	saveData();
	cout << endl;
	system("pause");
	createMenuGerirUsers();
}

void OLZ::adminMostraAnuncios()
{
	clrscr();
	impressaoTitulo();
	for (int i = 0; i < anuncios.size(); i++)
	{
		setcolor(4, 0);
		cout << anuncios[i]->getID() << " - " << anuncios[i]->getTitulo() << endl;
		setcolor(7, 0);
	}

	cout << endl;
	system("pause");
	createMenuGerirAnuncios();

}

void OLZ::MostraAnunciosUser(string mail)
{
	clrscr();
	impressaoTitulo();

	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->getAnunciante()->getEmail() == mail)
		{
			anuncios[i]->visAnuncio();

			cout << endl;
		}
	}

	cout << endl;
	system("pause");
	createMenuAnuncios();
}

vector<Anuncio * > OLZ::ordenaAnCat()
{
	vector<Anuncio *> temp = anuncios;

	for (unsigned int p = 1; p < temp.size(); p++)
	{
		Anuncio * tmp = temp[p];

		int j;

		for (j = p; j > 0 && tmp->getCategoria() < temp[j - 1]->getCategoria(); j--)
			temp[j] = temp[j - 1];
		temp[j] = tmp;
	}

	return temp;
}

vector<Anuncio * > OLZ::ordenaAnUt()
{
	vector<Anuncio *> temp = anuncios;

	for (unsigned int p = 1; p < temp.size(); p++)
	{
		Anuncio * tmp = temp[p];

		int j;

		for (j = p; j > 0 && tmp->getAnunciante()->getNome() < temp[j - 1]->getAnunciante()->getNome(); j--)
			temp[j] = temp[j - 1];
		temp[j] = tmp;
	}

	return temp;
}

vector<Anuncio * > OLZ::ordenaAnID()
{
	vector<Anuncio *> temp = anuncios;

	for (unsigned int p = 1; p < temp.size(); p++)
	{
		Anuncio * tmp = temp[p];

		int j;

		for (j = p; j > 0 && tmp->getID() < temp[j - 1]->getID(); j--)
			temp[j] = temp[j - 1];
		temp[j] = tmp;
	}

	return temp;
}

vector<Anuncio * > OLZ::pesquisaAnCat(string cat)
{
	vector<Anuncio * > temp;
	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->getCategoria() == cat)
			temp.push_back(anuncios[i]);
	}

	return temp;
}

vector<Anuncio * > OLZ::pesquisaAnTit(string tit)
{
	vector<Anuncio * > temp;
	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->getTitulo() == tit)
			temp.push_back(anuncios[i]);
	}

	return temp;
}

vector<Anuncio * > OLZ::pesquisaAnPreco(float p)
{
	vector<Anuncio * > temp;
	
	for (int i = 0; i < anuncios.size(); i++)
	{
		if (anuncios[i]->getPreco() <= p)
			temp.push_back(anuncios[i]);
	}

	return temp;
}
/*
vector<Anuncio * > OLZ::pesquisaAnPalavra(string p)
{
	vector<Anuncio *> temp;

	for (int i = 0; i < anuncios.size(); i++)
	{
		if ()
	}

}
*/

void OLZ::pesquisaPreco(float p)
{
	vector<Anuncio *> temp = pesquisaAnPreco(p);
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i]->visAnuncio();
	}
	return;
}

