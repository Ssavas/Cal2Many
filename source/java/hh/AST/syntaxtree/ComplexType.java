package hh.AST.syntaxtree;
import hh.common.translator.VisitorType;

import java.util.Map;


public class ComplexType extends Type {
	
	public Map<String, Exp> mval;
	public ComplexType(){
		mval=null;
	}
	
    public <T,E>T accept(VisitorType<T,E> v, E env) {
    	return v.visit(this,env);
  }
}
