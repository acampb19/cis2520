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
public class OtherActivity extends Activity{
    /**
     * 
     * @param list array list to hold all activities
     * @param title string to hold title of activity
     * @param stime string to hold user entered start time
     * @param etime string to hold user entered end time
     * @param location string to hold user entered location
     * @param comment string to hold user entered comment
     */
    public OtherActivity(ArrayList list, String title, String stime, String etime, String location, String comment)
    {
        super.makeList(list, "Other", title, stime, etime, location, comment);
    }
    
}
