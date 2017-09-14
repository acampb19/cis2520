/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dayplanner;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import javax.swing.JTextArea;

/**
 *
 * @author acampb19
 */
public class Activity {
    Scanner input = new Scanner(System.in);
    /**
     * 
     */
    /**
     * 
     */
    /**
     * 
     */
    /**
     * 
     */
    /**
     * 
     */
    public String title, stime, etime, comment, location;
    /** strings to hold type, start time, end time, comment and location of each activity
     * 
     */
    public int numtoken = 0;
    /** int to count the number of key words entered by user
     * 
     */
    public int prestoken = 0;
    /** int to count how many of the key words are actually in an activity
     * 
     */
    public int equals = 0;
    /** int to check if each activity fits all requirements
     * 
     */

    /**search method to search for activities
     * 
     * @param type string to hold the activity type
     * @param list array list for all activities
     * @param skey  string to hold user entered key words
     * @param sstart string to hold user entered start search time
     * @param sfinish   string to hold user entered end search time
     * @param result text area to receive search results
     */
    public void search(String type, ArrayList<String> list, String skey, String sstart, String sfinish, JTextArea result)
    {
        int i;/*counters*/
        int j = 0;
        int m = 0; /*identifier if types are the same*/
        String place = ""; /*string for type*/
        HashMap<String, ArrayList> map = new HashMap(); /*declaring and initializing hashmap*/ 
        ArrayList search = new ArrayList(); /*gets each line of array list*/
        for(String array : list)
        {
            j++;
            i=0;
            m = 0;
            String[] check = array.split(",");/*splits activity to get type and title*/
            for (String token : check) 
            {
                if(i == 0)
                {
                    place = token;/*first token is place*/
                    i++;
                }
                else if(i == 1)
                {
                    title = token;/*second token is title*/
                    i++;
                }
            }
            if(place.equalsIgnoreCase(type))
            {
                m=1; /*sets m = 1 if search type and activity type are the same*/ 
            }
            
            numtoken = 0; /*initializing token numbers to 0*/
            prestoken = 0;
            String[] keyword = skey.split(" ");/*splits to get each key word*/
            if(skey.equals("") && m == 1)
            {
                search.add(j);/*if no key words adds each line with the same activity type to arraylist*/
            }
            else if(!skey.equals("") && m == 1)
            {
                for (String token1 : keyword) /*if key words checks title for each word*/
                {
                    numtoken++;/*coutns number of key words*/
                    if((title.toLowerCase()).contains(token1.toLowerCase()))
                    {
                        prestoken++;/*counts number of key words actually in the title*/
                    }
                }
                if(numtoken == prestoken)
                {
                    search.add(j); /*if the all key words are in the title adds spot to arraylist*/
                }
            }

        }
        map.put(skey, search); /*adds string to hashmap with key words identifier*/
        search = map.get(skey); /*sets search string to map*/
        j=0;
        i=0;
        for(String array : list)
        {
            j++;
            if(search.contains(j))/*for each activity, checks if it is on the map list*/
            {
                if(sstart.equals("")&& sfinish.equals(""))/*if no user entered time brackets*/
                {
                    equals =1; /*each line fits conditions*/
                }
                else
                {
                    Time searchtime = new Time(); /*jumps to search time function*/
                    equals = searchtime.search(array, sstart, sfinish);
                }
                if(equals == 1)
                {
                    //if an activity matches the search criteria prints the activity to the result textbox
                    result.append(""+array+"\n");
                    i++;
                }
            } 
        }
    }
    
    
    /**
     * 
     * @param list array list to hold all activities
     * @param type string to hold type of activity
     * @param title string to hold user entered title
     * @param stime string to hold user entered start time
     * @param comment string to hold user entered comment
     * @param etime string to hold user entered end time
     * @param location string to hold user entered location
     */
    public void makeList(ArrayList list, String type, String title, String stime, String etime, String location, String comment)
    {
        if(type.equalsIgnoreCase("other"))
        {
            list.add(""+type+", "+title+", "+stime+", "+etime+", "+location+", "+comment);/*adds new activity to the array list*/
        }
        else
        {
            list.add(""+type+", "+title+", "+stime+", "+etime+", "+comment);/*adds new activity to the array list*/
        }
    }
}
    