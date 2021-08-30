#!/usr/bin/python -tt
# -*- coding: utf-8 -*-
class folha:
    def __init__(self,letra,folha=True,peso=1,direita=None, esquerda=None):
        self.letra=letra
        self.peso=peso
        self.folha=folha
        self.um=direita
        self.zero=esquerda
        self.dicionario={}
        self.dicionarioinvertido={}
    def incrementa(self):
        self.peso+=1
    def getPeso(self):
        return self.peso
    def getLetra(self):
        return self.letra
    
    def percorreArvore(self,sequencia=""):
        if self.zero!=None:
            self.zero.percorreArvore(sequencia+"0")
            self.dicionario={**self.dicionario,**self.zero.dicionario}
        if self.folha==True:
            #print(sequencia,self)
            self.dicionario[self.getLetra()]=sequencia
        if self.um!=None:
            self.um.percorreArvore(sequencia+"1")
            self.dicionario={**self.dicionario,**self.um.dicionario}
        
    def retornaDicionario(self,escolhe=True):
        if escolhe:
            return self.dicionario
        else:
            return self.dicionarioinvertido
    def invertedicionario(self):
        for i in self.dicionario:
            self.dicionarioinvertido[self.dicionario[i]]=i
    
    def __str__(self):
        return "'"+str(self.letra)+"'" +":"+ str(self.peso)
        

class Lista:
    def __init__(self):
        self.listagem=[]
    def inclui(self,letra):
        existe=False
        for i in self.listagem:
            if i.getLetra()==letra:
                existe=True
                i.incrementa()
        if not existe:
            self.listagem.append(folha(letra))
    def ordena(self):
        self.listagem.sort(key=lambda pares: pares.getPeso())
    def __str__(self):
        retorno="["
        for i in self.listagem:
            retorno+=str(i)+", "
        retorno=retorno[:-2]+"]"
        return retorno
    def junta(self):
        tam=len(self.listagem)
        if tam>1:
            self.listagem.append(folha(None,False,self.listagem[1].getPeso()+self.listagem[0].getPeso(),self.listagem.pop(0),self.listagem.pop(0)))
            self.ordena()
            return tam
        else:
            return 0
    def percorreArvore(self):
        ramo=self.listagem[0].percorreArvore()
        self.listagem[0].invertedicionario()
    def getDicionario(self,escolhe=True):
        return self.listagem[0].retornaDicionario(escolhe)
    def getDicionarioTexto(self):
        retorno=""
        for i in self.listagem[0].retornaDicionario(True):
            retorno+=i+":#:"+self.listagem[0].retornaDicionario(True)[i]+";"
        return retorno
def codificamensagem(mensagem,dic):
    mensagemcodigo=""
    for i in mensagem:
        mensagemcodigo+=dic[i]
    return mensagemcodigo
def decodificamensagem(mensagem,dic):
    mesagemdecodificada=""
    i=0
    for j in range(len(mensagem)+1):
        #print(mensagem[i:j],mensagem[i:j] in dic )
        if mensagem[i:j] in dic:
            mesagemdecodificada+=dic[mensagem[i:j]]            
            i=j
    return mesagemdecodificada
def montaDic(palavra):
    lista=palavra.split(";")
    #print (lista)
    dic={}
    for i in lista:
        if i!="":
            temp=i.split(":#:")
            #print(temp[0],temp[1])
            dic[temp[1]]=temp[0]
    return dic


def imprimeMenu():
    print("+----------------------------+")
    print("|           Menu             |")
    print("+----------------------------+")
    print("|1)Carregar Texto            |")
    print("|2)Gravar Texto              |")
    print("|3)Codificar texto           |")
    print("|4)Decodificar Texto         |")
    print("|5)Imprimir Texto            |")
    print("|6)Entrar Texto manualmente  |")

    print("|9)Sair                      |")
    print("+----------------------------+")

def menu():
    n=0
    while(n<1 or n>9):
        imprimeMenu()
        n=input(":")
        try:
            n= int(n)
        except:
            n=0
        if (n<1 or n>9):
            print("Resposta Invalida! \nTente novamente!")
    return n

def text_to_bits(text, encoding='utf-8', errors='surrogatepass'):
    bits = bin(int.from_bytes(text.encode(encoding, errors), 'big'))[2:]
    return bits.zfill(8 * ((len(bits) + 7) // 8))

def text_from_bits(bits, encoding='utf-8', errors='surrogatepass'):
    n = int(bits, 2)
    return n.to_bytes((n.bit_length() + 7) // 8, 'big').decode(encoding, errors) or '\0'        

def main():
    opcao=0
    texto=False
    caminho=r"\ "
    caminho=caminho[:-1]

    while(opcao!=9):
        opcao=menu()
        
        print(f"Voce selecionou a opção - {opcao}")
        if opcao==1:
            nome= input("Digite o nome do arquivo\n:")
            arquivo=open(caminho+nome,"r")
            leitura=arquivo.readlines()
            palavra=""
            texto=True
            arquivo.close()
            for i in leitura:
                palavra+=i
        elif opcao==2:
            if palavra==False:
                print("Abrir arquivo antes")
            else:
                nome= input("Digite o nome do arquivo\n:")
                arquivo=open(caminho+nome,"w")
                arquivo.write(palavra)
                arquivo.close()
                
        elif opcao==3:
            l= Lista()            
            for i in palavra:
                l.inclui(i)
            l.ordena()
            while (l.junta()>1):
                pass
            l.percorreArvore()
            palavra=codificamensagem(palavra,l.getDicionario(True))
            palavra= (l.getDicionarioTexto())+"\n#####!!#####&&#####*#####@#####\n"+palavra
        elif opcao==4:
            for i in leitura:
                palavra+=i
            palavra= palavra.split("\n#####!!#####&&#####*#####@#####\n")
            dicionario= montaDic(palavra[0])
            palavra=decodificamensagem(palavra[1],dicionario)
        elif opcao==5:
            print(palavra)
        elif opcao==6:
            palavra=input("Digite seu texto:")
            texto=True
        elif opcao==7:
            #palavra=text_from_bits(palavra)
            pass
        elif opcao==8:
            #palavra=text_to_bits(palavra)
            pass
        else:
            print("Saindo programa")
            
main()
