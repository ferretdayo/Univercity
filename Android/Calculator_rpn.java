package ya.Sample;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class Cal_RPN extends Activity {
	/*
	 * 変数flg -1:未記入 , 0:数字 , 1:/ , 2:* , 3:- , 4:+ , 5:=
	 */
	int flg = -1;
	/*
	 * 変数first_ope_flg 0:最初+,-の演算子が入力されている。 1:最初演算子ではなく数字を入力されている。
	 */
	int first_ope_flg = 0;
	/*
	 * 変数num_listは数字を入れる配列 変数ope_listは演算子を入れる配列 変数rnp_listは逆ポーランド記法に沿って代入された配列。
	 */
	ArrayList<String> form_list = new ArrayList<String>();
	Stack<String> ope_stack = new Stack<String>();
	Stack<String> rpn_stack = new Stack<String>();
	LinkedList<String> rpn_array = new LinkedList<String>();
	int first_stack = 1;
	int input_num_flg = 0;	//最初に1-9入力されたかどうか
	String formula = "";
	String num = "";
	int first = 1;
	String pre_ope = "";
	TextView tv;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		LinearLayout ll = new LinearLayout(this);
		ll.setOrientation(LinearLayout.VERTICAL);
		setContentView(ll);
		tv = new TextView(this);
		tv.setText("計算しましょう☆");
		tv.setTextSize(100);
		ll.addView(tv);
		TableLayout[] tl = new TableLayout[3];
		TableRow tr_ope = new TableRow(this);
		Button[] ope = new Button[6];
		int tl_cnt = 0;
		tl[tl_cnt] = new TableLayout(this);
		/*
		 * 演算子のTableLayoutを作成し、Buttonを作成。(演算子のButton)
		 */
		for (int i = 0; i < ope.length; i++) {
			ope[i] = new Button(this);
			switch (i) {
			case 0:
				ope[i].setText("/");
				ope[i].setId(-(i + 1));
				break;
			case 1:
				ope[i].setText("*");
				ope[i].setId(-(i + 1));
				break;
			case 2:
				ope[i].setText("-");
				ope[i].setId(-(i + 1));
				break;
			case 3:
				ope[i].setText("+");
				ope[i].setId(-(i + 1));
				break;
			case 4:
				ope[i].setText("=");
				ope[i].setId(-(i + 1));
				break;
			case 5:
				ope[i].setText("CA");
				ope[i].setId(-(i + 1));
				break;
			default:
				break;
			}
			ope[i].setOnClickListener(new CalClickListener());
			tr_ope.addView(ope[i]);
		}
		tl[tl_cnt].addView(tr_ope);
		ll.addView(tl[tl_cnt++]);
		int zero = 0;
		/*
		 * 電卓の数字の部分(1~9)のTableLayoutを作成。
		 */
		tl[tl_cnt] = new TableLayout(this);
		TableRow[] tr = new TableRow[3];
		Button[] bt = new Button[9];
		for (int i = 0; i < tr.length; i++) {
			tr[i] = new TableRow(this);
			for (int j = i * 3; j < bt.length / 3 + i * 3; j++) {
				bt[j] = new Button(this);
				bt[j].setText(Integer.toString(j + 1));
				bt[j].setId(j + 1);
				tr[i].addView(bt[j]);
				bt[j].setOnClickListener(new CalClickListener());
				zero = j + 2;
			}
			tl[tl_cnt].addView(tr[i]);
		}
		ll.addView(tl[tl_cnt++]);

		/*
		 * 0と0を表示させるTableLayout
		 */
		tl[tl_cnt] = new TableLayout(this);
		TableRow tr_zero = new TableRow(this);
		Button[] bt_zero = new Button[2];
		for (int i = 0; i < bt_zero.length; i++) {
			bt_zero[i] = new Button(this);
			switch (i) {
			case 0:
				bt_zero[i].setText("0");
				bt_zero[i].setId(zero);
				break;
			case 1:
				bt_zero[i].setText("00");
				bt_zero[i].setId(zero + i);
				break;
			default:
				break;
			}
			bt_zero[i].setOnClickListener(new CalClickListener());
			tr_zero.addView(bt_zero[i]);
		}
		tl[tl_cnt].addView(tr_zero);
		ll.addView(tl[tl_cnt]);
	}

	class CalClickListener implements OnClickListener {
		/*
		 * 計算結果を表示するメソッド
		 */
		private void Show(String ans) {
			tv.setText(ans);
		}

		/*
		 * 数字かどうか判定する正規表現
		 */
		private boolean checkStringNumber(String number) {
			Pattern p = Pattern.compile("^[0-9]+.?[0-9]*$|^-[0-9]+.?[0-9]*$");
			Matcher m = p.matcher(number);
			return m.find();
		}
		
		/*
		 * 演算子押された時の初期化
		 */
		private void ope_format(){
			num = "";
			input_num_flg = 0;
			first = 0;	
		}
		
		/*
		 * 数字押された場合の初期化
		 */
		private void num_format(){
			first_ope_flg = 1;
			input_num_flg = 1;	
			flg = 0;
		}

		/*
		 * 逆ポーランド記法を計算するメソッドcalculation_rpn
		 */
		private String calculation_rpn(LinkedList<String> rpn) {
			Stack<String> stack = new Stack<String>();
			double a = 0;
			double b = 0;
			while (true) {
				String word = rpn.poll();
				if (checkStringNumber(word)) { // 数字の時
					stack.push(word);
				} else {	//演算子の場合
					a = Double.parseDouble(stack.pop());
					b = Double.parseDouble(stack.pop());
					if (word.equals("+")) {
						rpn.addFirst(Double.toString(b + a));
					} else if (word.equals("-")) {
						rpn.addFirst(Double.toString(b - a));
					} else if (word.equals("/")) {
						rpn.addFirst(Double.toString(b / a));
					} else if (word.equals("*")) {
						rpn.addFirst(Double.toString(b * a));
					}
					while (!stack.empty()) {	//計算後、stackの中身を全てrpnの先頭に入れていく
						rpn.addFirst(stack.pop());
					}
					if (rpn.size() == 1 && checkStringNumber(rpn.get(0)))	//rpnのサイズが1の時かつ数字の時終了
						break;
				}
			}
			return rpn.get(0);
		}

		/*
		 * 数式を逆ポーランド記法変換するメソッドcreate_RPN
		 */
		private LinkedList<String> create_RPN(ArrayList<String> formula,
				LinkedList<String> pre) {
			LinkedList<String> rpn = new LinkedList<String>();
			HashMap<String, Integer> ope_priority = new HashMap<String, Integer>();
			/*
			 * 優先順位
			 */
			ope_priority.put("+", 1);
			ope_priority.put("-", 1);
			ope_priority.put("*", 2);
			ope_priority.put("/", 3);
			for (int i = 0; i < formula.size(); i++) {
				if (checkStringNumber(formula.get(i)) || pre.size() == 1) {
					if (pre.size() == 0) {	//"="を押したのが初めての時
						rpn.addLast(formula.get(i));
					} else {	//"="を押したのが1回以上の時、計算結果をrpnに最初入れる。
						rpn.addLast(pre.poll());
					}
				} else {
					/*
					 * ope_stackに何もないときは、演算子をope_stackにpushする。
					 * １．ある場合は、ope_stackにある一番最近入れた演算子と貰った演算子を比較し、
					 * 貰った演算子のほうが最近の演算子以上の大きさ　かつ　※最近の演算子が"/"かつもらった演算子が"/"でない場合
					 * ope_stackにpushする。
					 * (※:"/"が続くと　例）2/4/8　右から計算して、4になってしまうからである。
					 * そのため、"/"が続くと、rpnに演算子をpushするようにした。
					 * 2.貰った演算子が最近の演算子より小さい場合は、ope_stackにある演算子をrpnの最後に追加する。
					 * そのあと1.に戻る。
					 */
					while (true) {
						//1つ前の演算子を取得（はじめは、何もないので、0を代入
						int pre_ope = ope_stack.empty() ? 0 : ope_priority
								.get(ope_stack.get(ope_stack.size() - 1));
						if (ope_stack.empty()
								|| (ope_priority.get(ope_stack.get(ope_stack
										.size() - 1))/* 先頭の演算子 */<= ope_priority
										.get(formula.get(i))/* 貰った演算子 */&& !(pre_ope == 3 && ope_priority
										.get(formula.get(i)) == 3))) {
							ope_stack.push(formula.get(i));
							break;
						} else {
							rpn.addLast(ope_stack.pop());
						}
					}
				}
			}
			while (!ope_stack.empty()) { // 数字が全て出たので、演算子Stackの中身を全てrpnにpushする。
				rpn.addLast(ope_stack.pop());
			}
			return rpn;
		}

		public void onClick(View v) {
			/*
			 * 数式の取得(逆ポーランド記法に直す前)
			 */
			switch (v.getId()) {
			case -1:
				if (flg == 0 || flg == 5) {
					formula += "/";
					form_list.add(num);
					form_list.add("/");
					flg = 1;
					ope_format();
				}
				break;
			case -2:
				if (flg == 0 || flg == 5) {
					formula += "*";
					form_list.add(num);
					form_list.add("*");
					flg = 2;
					ope_format();
				}
				break;
			case -3:
				if (flg == -1 || flg == 0 || flg == 5) {
					formula += "-";
					if (first_ope_flg == 0) {
						num = "-";
					} else {
						form_list.add(num);
						form_list.add("-");
						ope_format();
					}
					flg = 3;
				}
				break;
			case -4:
				if (flg == -1 || flg == 0 || flg == 5) {
					formula += "+";
					if (first_ope_flg == 0) {
						num = "+";
					} else {
						form_list.add(num);
						form_list.add("+");
						ope_format();
					}
					flg = 4;
				}
				break;
			case -5:
				if (flg == 0) {
					if (first == 1) {
						Show(num);
					} else {
						form_list.add(num);
						rpn_array = create_RPN(form_list, rpn_array);
						num = calculation_rpn(rpn_array);
						form_list.clear();
						ope_stack.clear();
						rpn_stack.clear();
						Show(num);
					}
					flg = 5;
					input_num_flg = 0;
					formula = num;
					first = 1;
				}
				break;
			case -6:
				/*
				 * 初期化
				 */
				formula = "";
				flg = -1;
				first_ope_flg = 0;
				input_num_flg = 0;
				pre_ope = "";
				num = "";
				first_stack = 1;
				form_list.clear();
				rpn_array.clear();
				ope_stack.clear();
				rpn_stack.clear();
				break;
			case 1:
				if (flg >= -1 && flg <= 4) {
					formula += "1";
					num += "1";
					num_format();
				}
				break;
			case 2:
				if (flg >= -1 && flg <= 4) {
					formula += "2";
					num += "2";
					num_format();
				}
				break;
			case 3:
				if (flg >= -1 && flg <= 4) {
					formula += "3";
					num += "3";
					num_format();
				}
				break;
			case 4:
				if (flg >= -1 && flg <= 4) {
					formula += "4";
					num += "4";
					num_format();
				}
				break;
			case 5:
				if (flg >= -1 && flg <= 4) {
					formula += "5";
					num += "5";
					num_format();
				}
				break;
			case 6:
				if (flg >= -1 && flg <= 4) {
					formula += "6";
					num += "6";
					num_format();
				}
				break;
			case 7:
				if (flg >= -1 && flg <= 4) {
					formula += "7";
					num += "7";
					num_format();
				}
				break;
			case 8:
				if (flg >= -1 && flg <= 4) {
					formula += "8";
					num += "8";
					num_format();
				}
				break;
			case 9:
				if (flg >= -1 && flg <= 4) {
					formula += "9";
					num += "9";
					num_format();
				}
				break;
			case 10:
				if ((flg >= -1 && flg <= 0) || (flg >= 2 && flg <= 4)) {
					first_ope_flg = 1;
					formula += "0";
					num += "0";
					flg = 0;
				}
				break;
			case 11:
				if (flg == 0 && input_num_flg == 1) {
					first_ope_flg = 1;
					formula += "00";
					num += "00";
					flg = 0;
				}
				break;
			default:
				break;
			}
			if (flg != 5)
				tv.setText(formula);
		}
	}
}
