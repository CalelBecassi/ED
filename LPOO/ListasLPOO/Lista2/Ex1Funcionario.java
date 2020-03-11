public class Ex1Funcionario{
    String nome;
    String depart;
    double salario;
    String datEnt;
    String RG;

    void recebeAumento(double x){
        this.salario = this.salario + x;
    }

    double calculaGanhoAnual(){
        return this.salario * 12;
    }

    public static void main(String[] args){
        Ex1Funcionario func = new Ex1Funcionario();

        func.recebeAumento(5000);

        System.out.println(func.calculaGanhoAnual());
    }
}