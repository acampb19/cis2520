/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package dayplanner;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

/**
 *
 * @author acampb19
 */
public class DayPlanner {

    /**
     */
    public static ArrayList<String> activity = new ArrayList(); /*declaring and initializing array list*/
    public static String sstart,

    /**
     *
     */
    sfinish,

    /**
     *
     */
    infile,

    /**
     *
     */
    ofile; /*strings for user entered start time and end time and strings for input and output file names*/

    /**
     *
     */
    public static String type = ""; /*string for activity type*/

    /**
     *
     */
    public static String title = ""; /*string for activity title*/

    /**
     *
     */
    public static String stime=""; /*string for activity start time*/

    /**
     *
     */
    public static String etime=""; /*string for activity end time*/

    /**
     *
     */
    public static String comment; /*string for activity comment*/

    /**
     *
     */
    public static String location = ""; /*string for activity location*/
        
    /**
     *
     */
    public static class quitlistener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            int i;
            /*opens file for writing*/
                PrintWriter writer = null;
            try {
                writer = new PrintWriter(new FileOutputStream(ofile));
            } catch (FileNotFoundException ex) {
                Logger.getLogger(DayPlanner.class.getName()).log(Level.SEVERE, null, ex);
            }
                for(String array : activity)/*array is each line/activity of the array list*/
                {
                    i = 0;
                    String[] line = array.split(", "); /*splits string to every , */
                    for (String token : line) 
                    {
                        if(i == 0)/*first token is activity type*/
                        {
                            type = token;
                            writer.println("type = '"+token+"'"); /*writes new line in file*/
                            i++;
                        }
                        else if(i == 1)/*second token is activity title*/
                        {
                            writer.println("title = '"+token+"'");/*writes new line in file*/
                            i++;
                        }
                        else if(i == 2||i == 3||i == 4||i == 5||i == 6)/*3rd, 4th, 5th, 6th and 7th token are each element to start time of activity*/
                        {
                            if(i==2)
                            {
                                stime = token; /*adds year to string*/
                                stime = stime + ",";
                            }
                            else if(i==6)
                            {
                                stime = stime + token; /*adds minute to string*/
                                writer.println("start = '"+stime+"'");/*writes new line in file*/
                            }
                            else
                            {
                                stime = stime +token +",";/*adds month, day and hour to string*/
                            }
                            i++;
                        }
                        else if(i == 7||i == 8||i == 9||i == 10||i == 11)/*8th, 9th, 10th, 11th and 12th tokens are each element to end time of activity*/
                        {
                            if(i==7)
                            {
                                etime = token;/*adds year to string*/
                                etime = etime +",";
                            }
                            else if(i==11)
                            {
                                etime = etime+ token;/*adds minute to string*/
                                writer.println("end = '"+etime+"'");/*writes new line in file*/
                            }
                            else
                            {
                                etime = etime + token + ","; /*adds month, day and hour to string*/
                            }
                            i++;
                        }
                        else if(i == 12)/*13th token is location*/
                        {
                            if("other".equalsIgnoreCase(type))
                            {
                                writer.println("location = '"+token+"'");/*writes new line in file*/
                            }
                            i++;
                        }
                        else if(i == 13)/*14th token is comment*/
                        {
                            writer.println("comment = '"+token+"'");/*writes new line in file*/
                            writer.println("");/*writes new line in file*/
                        }
                    }
                }
                writer.close();/*closes file*/
            System.exit(0); /*closes all windows*/
        }
    }

    /**
     * function to add a new activity when the "ADD" option is selected from the commands bar
     */
    public static class addlistener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            final JFrame Window2 = new JFrame("Day Planner"); //creates a window for add activity
            Window2.setLayout(new BoxLayout(Window2.getContentPane(), BoxLayout.Y_AXIS));//sets the layout to be box layout
            Window2.setSize(500, 600); //sets window size
            JMenuBar bar = new JMenuBar();//creates a menu bar and adds ADD, SEARCH and QUIT options
            Window2.setJMenuBar(bar);
            JMenu Commands = new JMenu("Commands");
            bar.add(Commands);
            JMenuItem add = new JMenuItem ("ADD");
            Commands.add(add);
            JMenuItem search = new JMenuItem ("SEARCH");
            Commands.add(search);
            JMenuItem quit = new JMenuItem ("QUIT");
            Commands.add(quit);
            search.addActionListener(new searchlistener());//action listener for when search is selected
            quit.addActionListener(new quitlistener());//action listener for when quit is selected
            
            JLabel head = new JLabel("Adding an Activity: "); //jlabels to prompt user for different inputs
            JLabel type = new JLabel("Type: ");
            JLabel title = new JLabel("Title: ");
            JLabel stime = new JLabel("Start time(year, month, day, hour, minute): ");
            JLabel etime = new JLabel("End time(year, month, day, hour, minute): ");
            JLabel location = new JLabel("Location: ");
            JLabel comment = new JLabel("Comment: ");
            JLabel message = new JLabel("Messages: ");
            
            final JTextField titlebox = new JTextField(25);//text fields to recieve user inputs
            final JTextField stimebox = new JTextField(25);
            final JTextField etimebox = new JTextField(25);
            final JTextField locationbox = new JTextField(25);
            final JTextField commentbox = new JTextField(25);
            final JTextArea messagebox = new JTextArea(5, 25);//text area to display errors
            JScrollPane box = new JScrollPane(messagebox);//makes the text area scrollable
            box.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
            box.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
            messagebox.setEditable(false);//makes it so user can't write in the message box
            
            final JPanel headpanel = new JPanel();//jpanels for each input
            final JPanel typepanel = new JPanel();
            final JPanel stimepanel = new JPanel();
            final JPanel etimepanel = new JPanel();
            final JPanel titlepanel = new JPanel();
            final JPanel locationpanel = new JPanel();
            final JPanel commentpanel = new JPanel();
            final JPanel button = new JPanel();
            final JPanel messagepanel = new JPanel();
            final JPanel mbox = new JPanel();
            
            String[] items = {"School", "Home", "Other"};//string for the combo bar that holds activity types*/
            final JComboBox scroll = new JComboBox(items);
            
            //action listener to take in the activity type and project the specific window type
            scroll.addActionListener(new addlistener()
            {
                public void actionPerformed(ActionEvent e)
                {
                    String activ = (String)scroll.getSelectedItem(); //gets the activity type from the combo box
                    
                    //if other will display all panels
                    if("other".equalsIgnoreCase(activ))
                    {
                        Window2.getContentPane().removeAll();
                        Window2.add(headpanel);
                        Window2.add(typepanel);
                        Window2.add(titlepanel);
                        Window2.add(stimepanel);
                        Window2.add(etimepanel);
                        Window2.add(locationpanel);
                        Window2.add(commentpanel);
                        Window2.add(button);
                        Window2.add(messagepanel);
                        Window2.add(mbox);
                        Window2.setVisible(true);
                    }
                    //if school or home will not display the location panel
                    else
                    {
                        Window2.getContentPane().removeAll();
                        Window2.add(headpanel);
                        Window2.add(typepanel);
                        Window2.add(titlepanel);
                        Window2.add(stimepanel);
                        Window2.add(etimepanel);
                        Window2.add(commentpanel);
                        Window2.add(button);
                        Window2.add(messagepanel);
                        Window2.add(mbox);
                        Window2.setVisible(true);
                    }
                }
            });
            
            //button to refresh the text fields
            JButton refresh = new JButton("REFRESH");
            //action listener to refresh the text fields when refresh button is pressed
            refresh.addActionListener(new addlistener()
            {
                @Override
                public void actionPerformed(ActionEvent e)
                {
                    //sets the text in each text box to be nothing
                    titlebox.setText("");
                    stimebox.setText("");
                    etimebox.setText("");
                    locationbox.setText("");
                    commentbox.setText("");
                    messagebox.setText("");
                }
            });
            
            //Enter button
            JButton enter = new JButton("ENTER");
            
            //action listener to take user inputs when ENTER button is pressed
            enter.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e)
                {
                    //ints to hold start and finish times
                    int scount = 0;
                    int fcount = 0;
                    int error = 0;
                    int syear = 0;
                    int smonth = 0;
                    int sday = 0;
                    int shour = 0;
                    int sminute = 0;
                    int fyear = 0;
                    int fmonth = 0;
                    int fday = 0;
                    int fhour = 0;
                    int fminute = 0;
                    String type = ""; //strings to hold user inputs
                    String titlestring = "";
                    String stimestring = "";
                    String etimestring = "";
                    String locationstring = "";
                    String commentstring = "";
                    
                    //recieving user inputs
                    type = (String)scroll.getSelectedItem();
                    titlestring = titlebox.getText();
                    stimestring = stimebox.getText();
                    etimestring = etimebox.getText();
                    locationstring = locationbox.getText();
                    commentstring = commentbox.getText();
                    messagebox.setText("");
                    
                    //determines if start time is valid
                    if(!stimestring.equals(""))
                    {
                        //seperates year, month, day, minute and hour of start time respectively
                        String[] start = stimestring.split(","); 
                        for (String token: start)
                        {
                            scount++;
                            if(scount == 1)
                            {
                                syear = Integer.valueOf(token);
                                if(syear < 0)
                                {
                                    //checks if year is positive, if not prints an error message and counts an error
                                    messagebox.append("Invalid Start year\n");
                                    error++;
                                }
                            }
                            if(scount == 2)
                            {
                                smonth = Integer.valueOf(token);
                                if(smonth < 1 || smonth > 12)
                                {
                                    //checks if month is positive and below 12, if not prints an error message and counts an error
                                    messagebox.append("Invalid Start month\n");
                                    error++;
                                }
                            }
                            if(scount == 3)
                            {
                                sday = Integer.valueOf(token);
                                if(sday < 1 || sday > 31)
                                {
                                    //checks if day is above one and below 31, if not prints an error message and counts an error
                                    messagebox.append("Invalid Start day\n");
                                    error++;
                                }
                            }
                            if(scount == 4)
                            {
                                shour = Integer.valueOf(token);
                                if(shour < 0 || shour > 23)
                                {
                                    //checks if hour is positive and below 23, if not prints error message and counts error
                                    messagebox.append("Invalid Start hour\n");
                                    error++;
                                }
                            }
                            if(scount == 5)
                            {
                                sminute = Integer.valueOf(token);
                                if(sminute < 0 || sminute > 59)
                                {
                                    //checks if minute is positive and below 59, if not prints error message and counts error
                                    messagebox.append("Invalid Start minute\n");
                                    error++;
                                }
                            }
                        }
                    }
                    
                    //is user entered an end time, checks if time is valid
                    if(!etimestring.equals(""))
                    {
                        //splits up string to get year, month, day, hour and minute respectively
                        String[] finish = etimestring.split(","); 
                        for (String token: finish)
                        {
                            fcount++;
                            if(fcount == 1)
                            {
                                fyear = Integer.valueOf(token);
                                if(fyear < 0)
                                {
                                    //checks if year is positive, if not prints an error message and counts an error
                                    messagebox.append("Invalid End year\n");
                                    error++;
                                }
                            }
                            if(fcount == 2)
                            {
                                fmonth = Integer.valueOf(token);
                                if(fmonth < 1 || fmonth > 12)
                                {
                                    //checks if month is positive and below 12, if not prints an error message and counts an error
                                    messagebox.append("Invalid End month\n");
                                    error++;
                                }
                            }
                            if(fcount == 3)
                            {
                                fday = Integer.valueOf(token);
                                if(fday < 1 || fday > 31)
                                {
                                    //checks if day is above one and below 31, if not prints an error message and counts an error
                                    messagebox.append("Invalid End day\n");
                                    error++;
                                }
                            }
                            if(fcount == 4)
                            {
                                fhour = Integer.valueOf(token);
                                if(fhour < 0 || fhour > 23)
                                {
                                    //checks if hour is positive and below 23, if not prints error message and counts error
                                    messagebox.append("Invalid End hour\n");
                                    error++;
                                }
                            }
                            if(fcount == 5)
                            {
                                fminute = Integer.valueOf(token);
                                if(fminute < 0 || fminute > 59)
                                {
                                    //checks if minute is positive and below 59, if not prints error message and counts error
                                    messagebox.append("Invalid End minute\n");
                                    error++;
                                }
                            }
                        }
                    }
                    //checks if enough times entered
                    if(scount < 5)
                    {
                        messagebox.append("Error: not enough arguments in start time\n");
                    }
                    //checks if enough times are entered
                    if(fcount < 5)
                    {
                        messagebox.append("Error: not enough arguments in end time\n");
                    }
                    //compares times to see if start time is before end time
                    if(syear > fyear)
                    {
                        messagebox.append("Error: End time comes before Start time\n");
                        error++;
                    }
                    else if(syear == fyear)
                    {
                        if(smonth > fmonth)
                        {
                            messagebox.append("Error: End time comes before Start time\n");
                            error++;
                        }
                        else if(smonth == fmonth)
                        {
                            if(sday > fday)
                            {
                                messagebox.append("Error: End time comes before Start time\n");
                                error++;
                            }
                            else if(sday == fday)
                            {
                                if(shour > fhour)
                                {
                                    messagebox.append("Error: End time comes before Start time\n");
                                    error++;
                                }
                                else if(shour == fhour)
                                {
                                    if(sminute > fminute)
                                    {
                                        messagebox.append("Error: End time comes before Start time\n");
                                        error++;
                                    }
                                }
                            }
                        }
                    }
                    //if user selects home activity
                    if("home".equalsIgnoreCase(type))
                    {
                        //checks if user entered something in all text fields
                        if("".equals(titlestring) || "".equals(stimestring) || "".equals(etimestring))
                        {
                            messagebox.append("Missing some mandatory information\nPlease fill in the title, start time and end time\n");
                        }
                        //if user filled all text fields and there were no errors will add the activity and close the add window
                        else if(error == 0)
                        {
                            /*jumps to make list method in HomeActivity class within Activity class*/
                            HomeActivity homeact = new HomeActivity(activity, titlestring, stimestring, etimestring, locationstring, commentstring);
                            Window2.dispose();
                        }
                    }
                    //if user selects school activity
                    if("school".equalsIgnoreCase(type))
                    {
                        //checks if user entered something in all text fields
                        if("".equals(titlestring) || "".equals(stimestring) || "".equals(etimestring))
                        {
                            messagebox.append("Missing some mandatory information\nPlease fill in the title, start time and end time\n");
                        }
                        else if(error == 0)
                        {
                            /*jumps to make list method in SchoolActivity class within Activity class*/
                            SchoolActivity schoolact = new SchoolActivity(activity, titlestring, stimestring, etimestring, locationstring, commentstring);  
                            Window2.dispose();
                        }
                    }
                    //if user selects other activity
                    if("other".equalsIgnoreCase(type))
                    {
                        //checks if user entered something in all text fields
                        if("".equals(titlestring) || "".equals(stimestring) || "".equals(etimestring)|| "".equals(locationstring))
                        {
                            messagebox.append("Missing some mandatory information\nPlease fill in the title, start time, end time and location\n");
                        }
                        else if(error == 0)
                        {
                            /*jumps to make list method in OtherActivity class within Activity class*/
                            OtherActivity otheract = new OtherActivity(activity, titlestring, stimestring, etimestring, locationstring, commentstring);
                            Window2.dispose();
                        }
                    }
                }
            });
            
            //adds each label, text field, button and text area to their corresponding panel
            headpanel.add(head);
            typepanel.add(type);
            typepanel.add(scroll);
            titlepanel.add(title);
            titlepanel.add(titlebox);
            stimepanel.add(stime);
            stimepanel.add(stimebox);
            etimepanel.add(etime);
            etimepanel.add(etimebox);
            locationpanel.add(location);
            locationpanel.add(locationbox);
            commentpanel.add(comment);
            commentpanel.add(commentbox);
            button.add(refresh);
            button.add(enter);
            messagepanel.add(message);
            mbox.add(box);
            
            //adds each panel to the jfram
            Window2.add(headpanel);
            Window2.add(typepanel);
            Window2.add(titlepanel);
            Window2.add(stimepanel);
            Window2.add(etimepanel);
            Window2.add(commentpanel);
            Window2.add(button);
            Window2.add(messagepanel);
            Window2.add(mbox);
            //sets the jframe to be visible
            Window2.setVisible(true);
            
        }
    }

    /**
     * listener for when user selects the search option
     */
    public static class searchlistener implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e)
        {
            JFrame Window3 = new JFrame("Day Planner"); //creates new jframe for search window
            Window3.setLayout(new BoxLayout(Window3.getContentPane(), BoxLayout.Y_AXIS));//sets box layout
            Window3.setSize(500, 500);//sets size
            JMenuBar bar = new JMenuBar(); //creates menu bar for ADD, SEARCH and quit options
            Window3.setJMenuBar(bar);
            JMenu Commands = new JMenu("Commands");
            bar.add(Commands);
            JMenuItem add = new JMenuItem ("ADD");
            Commands.add(add);
            JMenuItem search = new JMenuItem ("SEARCH");
            Commands.add(search);
            JMenuItem quit = new JMenuItem ("QUIT");
            Commands.add(quit);
            add.addActionListener(new addlistener()); //jumps to add listener when user selects ADD
            quit.addActionListener(new quitlistener()); //quits program when user selects QUIT
            
            //jlabels for user input prompts
            JLabel head = new JLabel("Searching for an Activity: ");
            JLabel type = new JLabel("Type: ");
            JLabel title = new JLabel("Title: ");
            JLabel stime = new JLabel("Start time(year, month, day, hour, minute): ");
            JLabel etime = new JLabel("End time(year, month, day, hour, minute): ");
            JLabel results = new JLabel("Search Results: ");
            
            //text fields and areas to recieve user inputs
            final JTextField titlebox = new JTextField(25);
            final JTextField stimebox = new JTextField(25);
            final JTextField etimebox = new JTextField(25);
            final JTextArea sresult = new JTextArea(5, 25);
            JScrollPane box = new JScrollPane(sresult); //sets text area to be scrollable
            box.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
            box.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
            sresult.setEditable(false); //makes it so the user cannot write in the result box
            
            //jpanels for each search criteria
            JPanel headpanel = new JPanel();
            JPanel typepanel = new JPanel();
            JPanel stimepanel = new JPanel();
            JPanel etimepanel = new JPanel();
            JPanel titlepanel = new JPanel();
            JPanel button = new JPanel();
            JPanel resultpanel = new JPanel();
            JPanel resultbox = new JPanel();
            
            //creates a combo box for activity type
            String[] items = {"School", "Home", "Other", "All"};
            final JComboBox scroll = new JComboBox(items);
            
            //creates a refresh button
            JButton refresh = new JButton("REFRESH");
            //action listener for when REFRESH is pressed
            refresh.addActionListener(new addlistener()
            {
                @Override
                public void actionPerformed(ActionEvent e)
                {
                    //sets all text boxs to display nothing
                    titlebox.setText("");
                    stimebox.setText("");
                    etimebox.setText("");
                    sresult.setText("");
                }
            });
            //creates ENTER button
            JButton enter = new JButton("ENTER");
            
            //action listener for when ENTER is pressed
            enter.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e)
                {
                    //ints to hold start and finish times
                    int scount = 0;
                    int fcount = 0;
                    int error = 0;
                    int syear = 0;
                    int smonth = 0;
                    int sday = 0;
                    int shour = 0;
                    int sminute = 0;
                    int fyear = 0;
                    int fmonth = 0;
                    int fday = 0;
                    int fhour = 0;
                    int fminute = 0;
                    sresult.setText("");//sets text in result box to be nothing
                    String result = ""; //strings to hold user inputs
                    String type = "";
                    String titlestring = "";
                    String stimestring = "";
                    String etimestring = "";
                    //gets text from text fields
                    type = (String)scroll.getSelectedItem();
                    titlestring = titlebox.getText();
                    stimestring = stimebox.getText();
                    etimestring = etimebox.getText();
                    
                    //checks if start time is valid
                    if(!stimestring.equals(""))
                    {
                        String[] start = stimestring.split(","); /*tokenizes search start time*/
                        for (String token: start)
                        {
                            scount++;
                            if(scount == 1)
                            {
                                syear = Integer.valueOf(token);
                                if(syear < 0)
                                {
                                    //checks if year is positive, if not prints out error message and counts error
                                    sresult.append("Invalid Start year\n");
                                    error++;
                                }
                            }
                            if(scount == 2)
                            {
                                smonth = Integer.valueOf(token);
                                if(smonth < 1 || smonth > 12)
                                {
                                    //checks if month is between 1 and 12, if not prints out error message and counts error
                                    sresult.append("Invalid Start month\n");
                                    error++;
                                }
                            }
                            if(scount == 3)
                            {
                                sday = Integer.valueOf(token);
                                if(sday < 1 || sday > 31)
                                {
                                    //checks if day is between 1 and 31, if not prints out error message and counts error
                                    sresult.append("Invalid Start day\n");
                                    error++;
                                }
                            }
                            if(scount == 4)
                            {
                                shour = Integer.valueOf(token);
                                if(shour < 0 || shour > 23)
                                {
                                    //checks if hour is positive and below 23, if not prints out error message and counts error
                                    sresult.append("Invalid Start hour\n");
                                    error++;
                                }
                            }
                            if(scount == 5)
                            {
                                sminute = Integer.valueOf(token);
                                if(sminute < 0 || sminute > 59)
                                {
                                    //checks if minute is positive and below 60, if not prints out error message and counts error
                                    sresult.append("Invalid Start minute\n");
                                    error++;
                                }
                            }
                        }
                    }
                    //checks if end time is valid
                    if(!etimestring.equals(""))
                    {
                        String[] finish = etimestring.split(","); /*tokenizes search start time*/
                        for (String token: finish)
                        {
                            fcount++;
                            if(fcount == 1)
                            {
                                fyear = Integer.valueOf(token);
                                if(fyear < 0)
                                {
                                    //checks if year is positive, if not prints out error message and counts error
                                    sresult.append("Invalid End year\n");
                                    error++;
                                }
                            }
                            if(fcount == 2)
                            {
                                fmonth = Integer.valueOf(token);
                                if(fmonth < 1 || fmonth > 12)
                                {
                                    //checks if month is between 1 and 12, if not prints out error message and counts error
                                    sresult.append("Invalid End month\n");
                                    error++;
                                }
                            }
                            if(fcount == 3)
                            {
                                fday = Integer.valueOf(token);
                                if(fday < 1 || fday > 31)
                                {
                                    //checks if day is between 1 and 31, if not prints out error message and counts error
                                    sresult.append("Invalid End day\n");
                                    error++;
                                }
                            }
                            if(fcount == 4)
                            {
                                fhour = Integer.valueOf(token);
                                if(fhour < 0 || fhour > 23)
                                {
                                    //checks if hour is positive and below 24, if not prints out error message and counts error
                                    sresult.append("Invalid End hour\n");
                                    error++;
                                }
                            }
                            if(fcount == 5)
                            {
                                fminute = Integer.valueOf(token);
                                if(fminute < 0 || fminute > 59)
                                {
                                    //checks if minute is positive and below 60, if not prints out error message and counts error
                                    sresult.append("Invalid End minute\n");
                                    error++;
                                }
                            }   
                        }
                    }
                    //checks if not enough arguments in start time
                    if(scount >0 && scount < 5)
                    {
                        sresult.append("Error: not enough arguments in start time\n");
                    }
                    //checks if not enough arguments in end time
                    if(fcount > 0 && fcount < 5)
                    {
                        sresult.append("Error: not enough arguments in end time\n");
                    }
                    
                    //compares start and end time and returns an error message is start is after end time
                    if(syear > fyear)
                    {
                        sresult.append("Error: End time comes before Start time\n");
                        error++;
                    }
                    else if(syear == fyear)
                    {
                        if(smonth > fmonth)
                        {
                            sresult.append("Error: End time comes before Start time\n");
                            error++;
                        }
                        else if(smonth == fmonth)
                        {
                            if(sday > fday)
                            {
                                sresult.append("Error: End time comes before Start time\n");
                                error++;
                            }
                            else if(sday == fday)
                            {
                                if(shour > fhour)
                                {
                                    sresult.append("Error: End time comes before Start time\n");
                                    error++;
                                }
                                else if(shour == fhour)
                                {
                                    if(sminute > fminute)
                                    {
                                        sresult.append("Error: End time comes before Start time\n");
                                        error++;
                                    }
                                }
                            }
                        }
                    }
                    
                    if("all".equalsIgnoreCase(type) && error == 0)
                    {
                        //if user selects all will check all types
                        Activity searchlist = new Activity();  
                        searchlist.search("Home", activity, titlestring, stimestring, etimestring, sresult);
                        searchlist.search("School", activity, titlestring, stimestring, etimestring, sresult);
                        searchlist.search("Other", activity, titlestring, stimestring, etimestring, sresult);
                        
                        result = sresult.getText();
                        if("".equals(result))
                        {
                            //if nothing was printed to the result window, will say there were no matching activities
                            sresult.setText("No activities match this description");
                        }
                    }
                    //if user chooses home, school or other
                    else if(error == 0)
                    {
                        Activity searchlist = new Activity();  
                        searchlist.search(type, activity, titlestring, stimestring, etimestring, sresult);
                        
                        result = sresult.getText();
                        if("".equals(result))
                        {
                            //if nothing was printed to the result window, will say there were no matching activities
                            sresult.setText("No activities match this description");
                        }
                    }
                    
                }
            });
            
            //adds each label, textbox and button to corresponding panel
            headpanel.add(head); 
            typepanel.add(type);
            typepanel.add(scroll);
            titlepanel.add(title);
            titlepanel.add(titlebox);
            stimepanel.add(stime);
            stimepanel.add(stimebox);
            etimepanel.add(etime);
            etimepanel.add(etimebox);
            button.add(refresh);
            button.add(enter);
            resultpanel.add(results);
            resultbox.add(box);
            
            //adds all panels to the window
            Window3.add(headpanel);
            Window3.add(typepanel);
            Window3.add(titlepanel);
            Window3.add(stimepanel);
            Window3.add(etimepanel);
            Window3.add(button);
            Window3.add(resultpanel);
            Window3.add(resultbox);
            //sets window to be visible
            Window3.setVisible(true);
        }
    }
    
    /**
     *
     * @param args takes command line arguments
     * @throws IOException gets files
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        // TODO code application logic here
        int i = 0; /*counters*/
        int j = 0;
        
        if(args.length > 1)/*if 2 arguments on command line first is input file and second is output file*/
        {
            infile = args[0];
            ofile = args[1];
            
            Scanner inputStream = null;
            try/*tries to open file*/
            {
                inputStream = new Scanner(new FileInputStream(infile));/*opening file*/
            }
            catch(FileNotFoundException e)/*if can't open file exit program*/
            {
                System.out.println("File not found");
                System.exit(0);
            }
            String file;/*string to hold each line of file*/
            while(inputStream.hasNextLine()) /*checks if there is a next line in the file*/
            {
                file = inputStream.nextLine(); /*sets file equal to line of file*/
                String[] line = file.split("'"); /*splits file to every ' */
                for (String token : line) 
                {
                    if(i == 1 && j == 0)/*stores 2nd token to type*/
                    {
                        type = token;
                        i = 0;
                        j++;
                    }
                    else if(i == 1 && j == 1) /*stores 4 token to title*/
                    {
                        title = token;
                        i = 0;
                        j++;
                    }
                    else if(i == 1 && j == 2)/*stores 6th token to stime*/
                    {
                        stime = token;
                        i = 0;
                        j++;
                    }
                    else if(i == 1 && j == 3)/*stores 8th token to etime*/
                    {
                        etime = token;
                        i = 0;
                        j++;
                    }
                    else if(i == 1 && j == 4)/*stores 10th token to location if other and comment if not other*/
                    {
                        if("other".equalsIgnoreCase(type))
                        {
                            location = token;
                            i = 0;
                            j++;
                        }
                        else
                        {
                            comment = token;
                            activity.add(""+type+", "+title+", "+stime+", "+etime+", "+location+", "+comment); /*adds element to array list*/
                            i = -1;/*sets to -1 to skip empty line between activities*/
                            j=0;
                        }
                        
                    }
                    else if(i == 1 && j == 5)/*stores 12th token to comment if othe ractivity type*/
                    {
                        comment = token;
                        activity.add(""+type+", "+title+", "+stime+", "+etime+", "+location+", "+comment); /*adds element to array list*/
                        i = -1;/*sets to -1 to skip empty line between activities*/
                        j = 0;
                    }
                    else
                    {
                        i++;/*increments i to take every other token*/
                    }
                }
            }
        }
        else
        {
            ofile = args[0]; /*if only 1 argument, argument it output file name*/
        }
        
        JFrame firstWindow = new JFrame("Day Planner"); //creates new jframe
        firstWindow.setSize(500, 500);//sets the size of the jframe
        firstWindow.setLayout(new FlowLayout());//sets flow layout
        firstWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//allows exit if user clicks the x button
        JLabel greeting = new JLabel("<html><br><br><br>Welcome to the Day Planner!<br><br>Please choose a command from the Commands menu</html>");
        firstWindow.add(greeting);//adds the greeting to the window
        firstWindow.setVisible(true);//sets window to be visible
        JMenuBar bar = new JMenuBar();//creates a menu bar for commands such as ADD, SEARCH and QUIT
        firstWindow.setJMenuBar(bar);
        JMenu Commands = new JMenu("Commands");
        bar.add(Commands);
        JMenuItem add = new JMenuItem ("ADD");
        Commands.add(add);
        JMenuItem search = new JMenuItem ("SEARCH");
        Commands.add(search);
        JMenuItem quit = new JMenuItem ("QUIT");
        Commands.add(quit);
        add.addActionListener(new addlistener()); //action listener for ADD option
        search.addActionListener(new searchlistener()); //action listener for SEARCH option
        quit.addActionListener(new quitlistener()); //action listener for QUIT option
        
        
    }
}


