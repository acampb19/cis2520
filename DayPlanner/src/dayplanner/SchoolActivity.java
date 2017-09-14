/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dayplanner;

import java.util.ArrayList;

/**
 *
 * @author acampb19
 */
public class SchoolActivity extends Activity{
    /**
     * 
     * @param list array list to hold all activities
     * @param stime string to hold user entered start time
     * @param title string to hold title of activity
     * @param etime string to hold user entered end time
     * @param location string to hold user entered location
     * @param comment string to hold user entered comment
     */
    public SchoolActivity(ArrayList list, String title, String stime, String etime, String location, String comment)
    {
        super.makeList(list, "school", title, stime, etime, location, comment);
    }
}
