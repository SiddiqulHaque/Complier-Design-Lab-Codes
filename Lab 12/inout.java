import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class inout {
    public static void convert(String line,int[] block,HashMap<Integer,ArrayList<Integer>> inn,HashMap<Integer,ArrayList<Pair>> p,HashMap<Integer,ArrayList<Integer>> gen){
        if(line.charAt(1)=='-'){
            String[] s=line.split(" ");
            block[0]=s[0].charAt(0)-48;
            for(int i=1;i<s.length;i++){
                int a=Integer.parseInt(s[i]);
                if(inn.containsKey(a)){
                    ArrayList<Integer> arr=inn.get(a);
                    arr.add(block[0]);
                    inn.put(a,arr);
                }
                else{
                    ArrayList<Integer> arr=new ArrayList<>();
                    arr.add(block[0]);
                    inn.put(a,arr);
                }
            }
        }
        else{
            String[] s=line.split(" ");
            
                int a=Integer.parseInt(s[0]);
                char b=s[1].charAt(0);
                Pair c=new Pair(a, b);
                a=block[0];
                if(p.containsKey(a)){
                    ArrayList<Integer> ar=gen.get(a);
                    ar.add(c.a);
                    gen.put(a, ar);
                    ArrayList<Pair> arr=p.get(a);
                    arr.add(c);
                    p.put(a,arr);
                }
                else{
                    ArrayList<Integer> ar=new ArrayList<>();
                    ar.add(c.a);
                    gen.put(a, ar);
                    ArrayList<Pair> arr=new ArrayList<>();
                    arr.add(c);
                    p.put(a,arr);
                }

            
        }
    }
    public static boolean elementExists(ArrayList<Character> list, char element) {
        return list.contains(element);
    }
    public static void main(String[] args) throws IOException{
        System.out.println("Mohd Siddiqul Haque 21bcs037");
        String fileName="q12.txt";
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String line;
        HashMap<Integer,ArrayList<Integer>> map=new HashMap<>();
        HashMap<Integer,ArrayList<Pair>> p=new HashMap<>();
        HashMap<Integer,ArrayList<Integer>> gen=new HashMap<>();
        int[] block=new int[1];
        while ((line = br.readLine()) != null) {
            convert(line, block, map, p,gen);
        }
        HashMap<Integer,ArrayList<Integer>> kill=new HashMap<>();
        for (int key : map.keySet()) {
            ArrayList<Integer> value = map.get(key);
            ArrayList<Integer> arr=new ArrayList<>();
            ArrayList<Character> a=new ArrayList<>();
            ArrayList<Pair> b=p.get(key);
            for(int i=0;i<b.size();i++){
                a.add(b.get(i).b);
            }
            for(int i=0;i<value.size();i++){
                b=p.get(value.get(i));
                for(int j=0;j<b.size();j++){
                    if(elementExists(a, b.get(j).b)){
                        arr.add(b.get(j).a);
                    }
                }
            }
            kill.put(key, arr);

        }
        for(int key : gen.keySet()){
            System.out.print(key+" -> ");
            System.out.print("generates -> "+ gen.get(key));
            if(kill.containsKey(key)){
                System.out.print(" kills-> "+kill.get(key));
            }
            else{
                System.out.print(" kills-> []");
            }
            System.out.println();
        }


    }
}
class Pair{
    int a;
    char b;
    Pair(int a,char b){
        this.a=a;
        this.b=b;
    }
}