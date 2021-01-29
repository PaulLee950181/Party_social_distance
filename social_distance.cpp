#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
#include<iomanip>
#include<limits>

using namespace std;

class P{
	public:
		P( int id = 0, int x = 0, int y = 0 ){
			ID = id;
			X = x;
			Y = y;
		}
		double operator-( P p2 ){
			double distance;
			distance = sqrt( pow((X - p2.getX()), 2) + pow((Y - p2.getY()), 2) );
			return distance;
		}
		int getID(){
			return ID;
		}
		int getX(){
			return X;
		}
		int getY(){
			return Y;
		}
		void setX( int x ){
			X = x;
		}
		void setY( int y ){
			Y = y;
		}
		void setID( int id ){
			ID = id;
		}
	private:
		int ID, X, Y;
};

class OUT{
	friend ostream &operator<<( ostream &, const OUT & );
	public:
		OUT( int id1 = 0, int id2 = 0, double dis = 0 ){
			DIS = dis;
			if( id1 < id2 ){
				ID1 = id1;
				ID2 = id2;
			}
			else{
				ID1 = id2;
				ID2 = id1;
			}
		}
		int getID1(){
			return ID1;
		}
		int getID2(){
			return ID2;
		}
		double getDIS(){
			return DIS;
		}
		void setDIS( double dis ){
			DIS = dis;
		}
		void setID1( int id1 ){
			ID1 = id1;
		}
		void setID2( int id2 ){
			ID2 = id2;
		}
	private:
		int ID1, ID2;
		double DIS;
};

ostream &operator<<( ostream &output, const OUT &a ){
	output << a.ID1 << " " << a.ID2 << " " << fixed << setprecision(3) << a.DIS << endl;
	return output;
}

void MERGE_X( vector<P> &v, int p, int q, int r ){
	int n1 = q-p+1;
	int n2 = r-q;
	P L[n1+1];
	P R[n2+1];
	int i, j;
	for( i = 0 ; i < n1 ; i++ ){
		L[i] = v[p+i];
	}
	for( j = 0 ; j < n2 ; j++ ){
		R[j] = v[q+1+j];
	}
	L[n1].setX( 2147483600 );
	R[n2].setX( 2147483600 );
	i = 0;
	j = 0;
	for( int k = p ; k <= r ; k++ ){
		if( L[i].getX() < R[j].getX() ){
			v[k] = L[i];
			i++;
		}
		else{
			v[k] = R[j];
			j++;
		}
	}
}

void MSORT_X( vector<P> &v, int p, int r ){
	if( p < r ){
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		MSORT_X( v, p, q );
		MSORT_X( v, s, r );
		MERGE_X( v, p, q, r );
	}
}

void MERGE_Y( vector<P> &v, int p, int q, int r ){
	int n1 = q-p+1;
	int n2 = r-q;
	P L[n1+1];
	P R[n2+1];
	int i, j;
	for( i = 0 ; i < n1 ; i++ ){
		L[i] = v[p+i];
	}
	for( j = 0 ; j < n2 ; j++ ){
		R[j] = v[q+1+j];
	}
	L[n1].setY( 2147483600 );
	R[n2].setY( 2147483600 );
	i = 0;
	j = 0;
	for( int k = p ; k <= r ; k++ ){
		if( L[i].getY() < R[j].getY() ){
			v[k] = L[i];
			i++;
		}
		else{
			v[k] = R[j];
			j++;
		}
	}
}

void MSORT_Y( vector<P> &v, int p, int r ){
	if( p < r ){
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		MSORT_Y( v, p, q );
		MSORT_Y( v, s, r );
		MERGE_Y( v, p, q, r );
	}
}

void MERGE( vector<OUT> &v, int p, int q, int r ){
	int n1 = q-p+1;
	int n2 = r-q;
	OUT L[n1+1];
	OUT R[n2+1];
	int i, j;
	for( i = 0 ; i < n1 ; i++ ){
		L[i] = v[p+i];
	}
	for( j = 0 ; j < n2 ; j++ ){
		R[j] = v[q+1+j];
	}
	L[n1].setDIS( numeric_limits<double>::max() );
	R[n2].setDIS( numeric_limits<double>::max() );
	i = 0;
	j = 0;
	for( int k = p ; k <= r ; k++ ){
		if( L[i].getDIS() < R[j].getDIS() ){
			v[k] = L[i];
			i++;
		}
		else if( L[i].getDIS() == R[j].getDIS() ){
			if( L[i].getID1() < R[j].getID1() ){
				v[k] = L[i];
				i++;
			}
			else if( L[i].getID1() == R[j].getID1() ){
				if( L[i].getID2() < R[j].getID2() ){
					v[k] = L[i];
					i++;
				}
				else{
					v[k] = R[j];
					j++;
				}
			}
			else{
				v[k] = R[j];
				j++;
			}
		}
		else{
			v[k] = R[j];
			j++;
		}
	}
}

void MSORT( vector<OUT> &v, int p, int r ){
	if( p < r ){
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		MSORT( v, p, q );
		MSORT( v, s, r );
		MERGE( v, p, q, r );
	}
}

void M_1_MID( vector<P> &v, vector<OUT> &ans, int q, double D ){
	double mid, midm, midp;
	OUT ans_temp;
	mid = v[q].getX();
	midm = mid - D;
	midp = mid + D;
	vector<P> temp;
	temp.push_back(v[q]);
	int i = q - 1;
	while( v[i].getX() >= midm ){
		temp.push_back(v[i]);
		i--;
	}
	int j = q + 1;
	while( v[j].getX() <= midp ){
		temp.push_back( v[j] );
		j++;
	}
	MSORT_Y( temp, 0, (temp.size() - 1) );
	for( int i = 1 ; i < temp.size() ; i++ ){
		for( int j = 0 ; j < i ; j++ ){
			if( (temp[i].getY() - temp[j].getY()) > D ){
				break;
			}
			else{
				ans_temp.setDIS( v[j] - v[i] );
				if( v[j].getID() < v[i].getID() ){
					ans_temp.setID1( v[j].getID() );
					ans_temp.setID2( v[i].getID() );
				}
				else{
					ans_temp.setID1( v[i].getID() );
					ans_temp.setID2( v[j].getID() );
				}
				if( ans_temp.getDIS() < D ){
					ans.push_back(ans_temp);
				}
			}
		}
	}
}

void M_1( vector<P> &v, vector<OUT> &ans, int p, int r, double D ){
	OUT ans_temp;
	if( p - r < 3 ){
		for( int i = p + 1 ; i <= r ; i++ ){
			for( int j = p ; j < i ; j++ ){
				ans_temp.setDIS( v[j] - v[i] );
				if( v[j].getID() < v[i].getID() ){
					ans_temp.setID1( v[j].getID() );
					ans_temp.setID2( v[i].getID() );
				}
				else{
					ans_temp.setID1( v[i].getID() );
					ans_temp.setID2( v[j].getID() );
				}
				if( ans_temp.getDIS() < D ){
					ans.push_back(ans_temp);
				}
			}
		}
	}
	else{
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		M_1( v, ans, p, q, D );
		M_1( v, ans, s, r, D );
		M_1_MID( v, ans, q, D );
	}
}

OUT MIN_DIS_MID( vector<P> v, int q, double ans_DIS ){
	double mid, midm, midp;
	OUT mid_ans;
	mid_ans.setDIS( numeric_limits<double>::max() );
	mid = v[q].getX();
	midm = mid - ans_DIS;
	midp = mid + ans_DIS;
	vector<P> temp;
	temp.push_back(v[q]);
	int i = q - 1;
	while( v[i].getX() >= midm ){
		temp.push_back(v[i]);
		i--;
	}
	int j = q + 1;
	while( v[j].getX() <= midp ){
		temp.push_back( v[j] );
		j++;
	}
	MSORT_Y( temp, 0, (temp.size() - 1) );
	OUT mid_ans_temp;
	for( int k = 0 ; k < temp.size() ; k++ ){
		int TIMES;
		if( (temp.size() - k) < 9 ){
			TIMES = temp.size();
		}
		else{
			TIMES = k + 8;
		}
		for( int ii = k + 1 ; ii < TIMES ; ii++ ){
			mid_ans_temp.setDIS(temp[k] - temp[ii]);
			if( temp[k].getID() < temp[ii].getID() ){
				mid_ans_temp.setID1( temp[k].getID() );
				mid_ans_temp.setID2( temp[ii].getID() );
			}
			else{
				mid_ans_temp.setID1( temp[ii].getID() );
				mid_ans_temp.setID2( temp[k].getID() );
			}
			if( mid_ans_temp.getDIS() < mid_ans.getDIS() ){
				mid_ans = mid_ans_temp;				
			}
			else if( mid_ans_temp.getDIS() == mid_ans.getDIS() ){
				if( mid_ans_temp.getID1() < mid_ans.getID1() ){
					mid_ans = mid_ans_temp;
				}
				else if( mid_ans_temp.getID1() == mid_ans.getID1() ){
					if( mid_ans_temp.getID2() < mid_ans.getID2() ){
						mid_ans = mid_ans_temp;
					}
				}
			}
		}
	}
	return mid_ans;
}

OUT MIN_DIS( vector<P> v, int p, int r ){
	OUT ans;	
	if( p - r < 3 ){
		OUT ans_temp;
		ans.setDIS( numeric_limits<double>::max() );
		for( int i = p + 1 ; i <= r ; i++ ){
			for( int j = p ; j < i ; j++ ){
				ans_temp.setDIS( v[j] - v[i] );
				if( v[j].getID() < v[i].getID() ){
					ans_temp.setID1( v[j].getID() );
					ans_temp.setID2( v[i].getID() );
				}
				else{
					ans_temp.setID1( v[i].getID() );
					ans_temp.setID2( v[j].getID() );
				}
				if( ans_temp.getDIS() < ans.getDIS() ){
					ans = ans_temp;
				}
				else if( ans_temp.getDIS() == ans.getDIS() ){
					if( ans_temp.getID1() < ans.getID1() ){
						ans = ans_temp;
					}
					else if( ans_temp.getID1() == ans.getID1() ){
						if( ans_temp.getID2() < ans.getID2() ){
							ans = ans_temp;
						}
					}
				}
			}
		}
	}
	else{
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		OUT ans_l, ans_r, ans_m;
		ans_l = MIN_DIS( v, p, q );
		ans_r = MIN_DIS( v, s, r );
		if( ans_l.getDIS() < ans_r.getDIS() ){
			ans = ans_l;
		}
		else if( ans_l.getDIS() == ans_r.getDIS() ){
			if( ans_l.getID1() < ans_r.getID1() ){
				ans = ans_l;
			}
			else if( ans_l.getID1() == ans_r.getID1() ){
				if( ans_l.getID2() < ans_r.getID2() ){
					ans = ans_l;
				}
				else{
					ans = ans_r;
				}
			}
			else{
				ans = ans_r;
			}
		}
		else{
			ans = ans_r;
		}
		ans_m = MIN_DIS_MID( v, q, ans.getDIS() );
		if( ans_m.getDIS() < ans.getDIS() ){
			ans = ans_m;
		}
		else if( ans_m.getDIS() == ans.getDIS() ){
			if( ans_m.getID1() < ans.getID1() ){
				ans = ans_m;
			}
			else if( ans_m.getID1() == ans.getID1() ){
				if( ans_m.getID2() < ans.getID2() ){
					ans = ans_m;
				}
			}
		}
	}
	return ans;
}

OUT MIN_DIS_MID_2( vector<P> v, int q, double ans_DIS, OUT last_ans ){
	double mid, midm, midp;
	OUT mid_ans;
	OUT mid_ans_temp;
	mid_ans.setDIS( numeric_limits<double>::max() );
	mid = v[q].getX();
	midm = mid - ans_DIS;
	midp = mid + ans_DIS;
	vector<P> temp;
	temp.push_back(v[q]);
	int i = q - 1;
	while( v[i].getX() >= midm ){
		temp.push_back(v[i]);
		i--;
	}
	int j = q + 1;
	while( v[j].getX() <= midp ){
		temp.push_back( v[j] );
		j++;
	}
	MSORT_Y( temp, 0, (temp.size() - 1) );
	for( int k = 0 ; k < temp.size() ; k++ ){
		int TIMES;
		if( (temp.size() - k) < 9 ){
			TIMES = temp.size();
		}
		else{
			TIMES = k + 8;
		}
		for( int ii = k + 1 ; ii < TIMES ; ii++ ){
			mid_ans_temp.setDIS(temp[k] - temp[ii]);
			if( temp[k].getID() < temp[ii].getID() ){
				mid_ans_temp.setID1( temp[k].getID() );
				mid_ans_temp.setID2( temp[ii].getID() );
			}
			else{
				mid_ans_temp.setID1( temp[ii].getID() );
				mid_ans_temp.setID2( temp[k].getID() );
			}
			if( mid_ans_temp.getDIS() == last_ans.getDIS() ){
				if( mid_ans_temp.getID1() > last_ans.getID1() ){
					if( mid_ans_temp.getDIS() < mid_ans.getDIS() ){
						mid_ans = mid_ans_temp;				
					}
					else if( mid_ans_temp.getDIS() == mid_ans.getDIS() ){
						if( mid_ans_temp.getID1() < mid_ans.getID1() ){
							mid_ans = mid_ans_temp;
						}
						else if( mid_ans_temp.getID1() == mid_ans.getID1() ){
							if( mid_ans_temp.getID2() < mid_ans.getID2() ){
								mid_ans = mid_ans_temp;
							}
						}
					}
				}
				else if( mid_ans_temp.getID1() == last_ans.getID1() ){
					if( mid_ans_temp.getID2() > last_ans.getID2() ){
						if( mid_ans_temp.getDIS() < mid_ans.getDIS() ){
							mid_ans = mid_ans_temp;				
						}
						else if( mid_ans_temp.getDIS() == mid_ans.getDIS() ){
							if( mid_ans_temp.getID1() < mid_ans.getID1() ){
								mid_ans = mid_ans_temp;
							}
							else if( mid_ans_temp.getID1() == mid_ans.getID1() ){
								if( mid_ans_temp.getID2() < mid_ans.getID2() ){
									mid_ans = mid_ans_temp;
								}
							}
						}
					}
				}
			}
			else if( mid_ans_temp.getDIS() > last_ans.getDIS() ){
				if( mid_ans_temp.getDIS() < mid_ans.getDIS() ){
					mid_ans = mid_ans_temp;				
				}
				else if( mid_ans_temp.getDIS() == mid_ans.getDIS() ){
					if( mid_ans_temp.getID1() < mid_ans.getID1() ){
						mid_ans = mid_ans_temp;
					}
					else if( mid_ans_temp.getID1() == mid_ans.getID1() ){
						if( mid_ans_temp.getID2() < mid_ans.getID2() ){
							mid_ans = mid_ans_temp;
						}
					}
				}
			}			
		}
	}
	return mid_ans;
}

OUT MIN_DIS_2( vector<P> v, int p, int r, OUT last_ans ){
	OUT ans;	
	if( p - r < 3 ){
		OUT ans_temp;
		ans.setDIS( numeric_limits<double>::max() );
		for( int i = p + 1 ; i <= r ; i++ ){
			for( int j = p ; j < i ; j++ ){
				ans_temp.setDIS( v[j] - v[i] );
				if( v[j].getID() < v[i].getID() ){
					ans_temp.setID1( v[j].getID() );
					ans_temp.setID2( v[i].getID() );
				}
				else{
					ans_temp.setID1( v[i].getID() );
					ans_temp.setID2( v[j].getID() );
				}
				
				
				if( ans_temp.getDIS() == last_ans.getDIS() ){
					if( ans_temp.getID1() > last_ans.getID1() ){
						if( ans_temp.getDIS() < ans.getDIS() ){
							ans = ans_temp;				
						}
						else if( ans_temp.getDIS() == ans.getDIS() ){
							if( ans_temp.getID1() < ans.getID1() ){
								ans = ans_temp;
							}
							else if( ans_temp.getID1() == ans.getID1() ){
								if( ans_temp.getID2() < ans.getID2() ){
									ans = ans_temp;
								}
							}
						}
					}
					else if( ans_temp.getID1() == last_ans.getID1() ){
						if( ans_temp.getID2() > last_ans.getID2() ){
							if( ans_temp.getDIS() < ans.getDIS() ){
								ans = ans_temp;				
							}
							else if( ans_temp.getDIS() == ans.getDIS() ){
								if( ans_temp.getID1() < ans.getID1() ){
									ans = ans_temp;
								}
								else if( ans_temp.getID1() == ans.getID1() ){
									if( ans_temp.getID2() < ans.getID2() ){
										ans = ans_temp;
									}
								}
							}
						}
					}
				}
				else if( ans_temp.getDIS() > last_ans.getDIS() ){
					if( ans_temp.getDIS() < ans.getDIS() ){
						ans = ans_temp;				
					}
					else if( ans_temp.getDIS() == ans.getDIS() ){
						if( ans_temp.getID1() < ans.getID1() ){
							ans = ans_temp;
						}
						else if( ans_temp.getID1() == ans.getID1() ){
							if( ans_temp.getID2() < ans.getID2() ){
								ans = ans_temp;
							}
						}
					}
				}				
			}
		}
	}
	else{
		int q, s;
		q = ( p + r ) / 2;
		s = q + 1;
		OUT ans_l, ans_r, ans_m;
		ans_l = MIN_DIS_2( v, p, q, last_ans );
		ans_r = MIN_DIS_2( v, s, r, last_ans );
		if( ans_l.getDIS() < ans_r.getDIS() ){
			ans = ans_l;
		}
		else if( ans_l.getDIS() == ans_r.getDIS() ){
			if( ans_l.getID1() < ans_r.getID1() ){
				ans = ans_l;
			}
			else if( ans_l.getID1() == ans_r.getID1() ){
				if( ans_l.getID2() < ans_r.getID2() ){
					ans = ans_l;
				}
				else{
					ans = ans_r;
				}
			}
			else{
				ans = ans_r;
			}
		}
		else{
			ans = ans_r;
		}
		ans_m = MIN_DIS_MID_2( v, q, ans.getDIS(), last_ans );
		if( ans_m.getDIS() < ans.getDIS() ){
			ans = ans_m;
		}
		else if( ans_m.getDIS() == ans.getDIS() ){
			if( ans_m.getID1() < ans.getID1() ){
				ans = ans_m;
			}
			else if( ans_m.getID1() == ans.getID1() ){
				if( ans_m.getID2() < ans.getID2() ){
					ans = ans_m;
				}
			}
		}
	}
	return ans;
}


int main( int argc, char *argv[] ){
	ifstream input;
	input.open( argv[1] );
	ofstream output;
	output.open( argv[2] );
	int NP, id, x, y, mode, N;
	double D;
	input >> NP;
	vector<P> num(NP);
	for( int i = 0 ; i < NP ; i++ ){
		input >> id >> x >> y;
		P temp( id, x, y );
		num[i] = temp;
	}
	MSORT_X( num, 0, (NP-1) );
	input >> mode;
	if( mode == 3 ){
		OUT ans = MIN_DIS( num, 0, (NP-1) );
		output << "1" << endl << ans;
	}
	else if( mode == 2 ){
		input >> N;
		output << N << " " << endl;
		if( N != 0 ){
			OUT last_ans;
			last_ans = MIN_DIS( num, 0, (NP-1) );
			output << last_ans;
			for( int j = 1 ; j < N ; j++ ){
				last_ans = MIN_DIS_2( num, 0, (NP-1), last_ans );
				output << last_ans;
			}
		}
	}
	else if( mode == 1 ){
		vector<OUT> m1;
		input >> D;
		M_1( num, m1, 0, (NP-1), D );
		MSORT( m1, 0, (m1.size()-1) );
		output << m1.size() << " " << endl;
		if( m1.size() != 0 ){		
			for( int k = 0 ; k < m1.size() ; k++ ){
				output << m1[k];
			}
		}
	}
	return 0;
}










