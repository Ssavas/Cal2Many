package hh.AST.syntaxtree;
import hh.common.translator.VisitorExp;

import hh.common.translator.VisitorExp;
public class BitAnd extends Exp {
  public Exp e1,e2;
  
  public BitAnd(Exp ae1, Exp ae2) { 
    e1=ae1; e2=ae2;
  }

  public <T,E>T accept(VisitorExp<T,E> v, E env) {
	return v.visit(this,env);
  }
}
