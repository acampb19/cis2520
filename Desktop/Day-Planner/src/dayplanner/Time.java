/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dayplanner;

/**
 *
 * @author acampb19
 */
public class Time {
    /**
     * 
     * @param array string to hold each activity from the arraylist
     * @param sstart user entered start time for search
     * @param sfinish user entered end time for search
     * @return returns 0 if activity times are not within search times, returns 1 when activity times are within search times
     */
    public int search(String array, String sstart, String sfinish)
    {
        int p = 0;
        int searchyear = 0;/*ints for each time*/
        int searchmonth = 0;
        int searchday = 0;
        int searchhour = 0;
        int searchminute = 0;
        int fsearchyear = 0;
        int fsearchmonth = 0;
        int fsearchday = 0;
        int fsearchhour = 0;
        int fsearchminute = 0;
        int startyear = 0;
        int startmonth = 0;
        int startday = 0;
        int starthour = 0;
        int startminute = 0;
        int finishyear = 0;
        int finishmonth = 0;
        int finishday = 0;
        int finishhour = 0;
        int finishminute = 0;
        String[] stime = sstart.split(","); /*tokenizes search start time*/
        for (String token: stime)
        {
            if(p==0)
            {
                searchyear = Integer.valueOf(token);
                p++;
            }
            if(p==1)
            {
                searchmonth = Integer.valueOf(token);
                p++;
            }
            if(p == 3)
            {
                searchday = Integer.valueOf(token);
                p++;
            }
            if(p == 4)
            {
                searchhour = Integer.valueOf(token);
                p++;
            }
            if(p == 5)
            {
                searchminute = Integer.valueOf(token);
                p++;
            }
        }
        p = 0;
        String[] ftime = sfinish.split(", ");/*tokenizes search finish time*/
        for (String token: ftime)
        {
            if(p==0)
            {
                fsearchyear = Integer.valueOf(token);
                p++;
            }
            if(p==1)
            {
                fsearchmonth = Integer.valueOf(token);
                p++;
            }
            if(p == 3)
            {
                fsearchday = Integer.valueOf(token);
                p++;
            }
            if(p == 4)
            {
                fsearchhour = Integer.valueOf(token);
                p++;
            }
            if(p == 5)
            {
                fsearchminute = Integer.valueOf(token);
                p++;
            }
        }
        p = 0;
        String[] starttime = array.split(", "); /*tokenizes activity to get times*/
        for (String token: starttime)
        {
            if(p==2)
            {
                startyear = Integer.valueOf(token);
            }
            if(p==3)
            {
                startmonth = Integer.valueOf(token);
            }
            if(p == 4)
            {
                startday = Integer.valueOf(token);
            }
            if(p == 5)
            {
                starthour = Integer.valueOf(token);
            }
            if(p == 6)
            {
                startminute = Integer.valueOf(token);
            }
            if(p==7)
            {
                finishyear = Integer.valueOf(token);
            }
            if(p==8)
            {
                finishmonth = Integer.valueOf(token);
            }
            if(p == 9)
            {
                finishday = Integer.valueOf(token);
            }
            if(p == 10)
            {
                finishhour = Integer.valueOf(token);
            }
            if(p == 11)
            {
                finishminute = Integer.valueOf(token);
            }
            p++;
        }
        /*compares each year, month, day, hour and minute. Return 1 if activity time is within search time and 0 if not*/
        if(searchyear < startyear && fsearchyear > finishyear)
        {
            return 1;
        }
        else if(searchyear == startyear && fsearchyear > finishyear )
        {
            if(searchmonth < startmonth)
            {
                return 1;
            }
            else if(searchmonth == startmonth)
            {
                if(searchday < startday)
                {
                    return 1;
                }
                else if(searchday == startday)
                {
                    if(searchhour < starthour)
                    {
                        return 1;
                    }
                    else if(searchhour == starthour)
                    {
                        if(searchminute < startminute)
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else if(searchyear < startyear && fsearchyear == finishyear)
        {
            if(fsearchmonth > finishmonth)
            {
                return 1;
            }
            else if(fsearchmonth == finishmonth)
            {
                if(fsearchday > finishday)
                {
                    return 1;
                }
                else if(fsearchday == finishday)
                {
                    if(fsearchhour > finishhour)
                    {
                        return 1;
                    }
                    else if(fsearchhour == finishhour)
                    {
                        if(fsearchminute > finishminute)
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                { 
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }    
    }
}
