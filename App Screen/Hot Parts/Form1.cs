/*   6/25/2014   Author:  Nick Hollis
 * 
 *   This app will call a stored procedure that pulls information 
 *   about "App Screen" and displays the information in a form with 
 *   a split screen.  The screen will refresh at a regular interval.
 *   
 *   The screen takes arguements that help adjust the scope of 
 *   data being pulled and displayed.  The screen can then be 
 *   refreshed by button push if not already at the end of a
 *   refresh interval.
 *   
 *   This app runs on loop as an event driven screen, updating at 
 *   regular intervals until a user Exits the program.
 *   
 *   ### Names of variables, connection strings, stored procedures, 
 *       etc. have been changed.  Version also changed to .NET 4.0 
 *       (down from 4.5) for compatability issues ###
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient; //database connection

namespace App_Screen
{
    public partial class Form1 : Form
    {
        string site = "Site1";   //default
        int refresh_minutes = 2;      //default of 2 minutes for refresh rate
        int weeksBefore = 4;    //default of past 4 weeks
        int weeksAfter = 2;     //default of 2 weeks out
        int Days = 10;   //default 10 days
        string strConnection = App_Screen.Properties.Settings.Default.Connection1;
        bool bottom = false;    //is bottom of the App Screen scroll bar reached
        int previous1 = -1;    //to store when scroll bar App Screen reaches bottom
        int previous2 = -1;     //to store when scroll bar App Screen 2 reaches bottom
        bool AppScreenScroll = false;   //track if AppScreen data set is long enough to scroll
        bool AppScreen2Scroll = false;    //track if App Screen 2 data set is long enough to scroll
        bool first_update = true;  //switch for first update vs subsequent updates
        float font_size = (float)19;
        int width = 1920;  //default width
        public Form1()
        {
            try
            {
                InitializeComponent();
                splitContainer1.Panel1.AutoScroll = true;   //set both left and right sub-panels to autoscroll vertically
                splitContainer1.Panel2.AutoScroll = true;
                toolStrip1.Dock = System.Windows.Forms.DockStyle.Top;   //set the tool strip at the top of the window

                WindowState = FormWindowState.Maximized;        //set the window to auto-maximize on load
                int height = Screen.PrimaryScreen.Bounds.Height;    //get the height and width of the screen.  
                width = Screen.PrimaryScreen.Bounds.Width;      //width is stored globally to later determine column width

                splitContainer1.Width = width;      //set the container to current screen width inside the window
                splitContainer1.Height = height - toolStrip1.Height;    //subtract tool strip height from screen height and set container to that height inside the window
                splitContainer1.Panel1.Anchor = System.Windows.Forms.AnchorStyles.Left;     //anchor sub-panels to the left and right respectively
                splitContainer1.Panel2.Anchor = System.Windows.Forms.AnchorStyles.Right;

                splitContainer1.SplitterDistance = (int)(0.2 * width);  //set initial distance of splitter between sub-panels 

                dgvAppScreen.Dock = System.Windows.Forms.DockStyle.Fill;     //set data grid views to fill the sub-panels respectively
                dgvAppScreen2.Dock = System.Windows.Forms.DockStyle.Fill;

                dgvAppScreen.RowHeadersVisible = false;  //hide row headers as they are not needed
                dgvAppScreen2.RowHeadersVisible = false;

                dgvAppScreen.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.None;     //use for defining sizes based on screen width in update, we do not want to autosize
                dgvAppScreen2.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.None;

                dgvAppScreen.AlternatingRowsDefaultCellStyle.BackColor = Color.LightGray;    //set rows to alternate white and gray background color for easier reading
                dgvAppScreen2.AlternatingRowsDefaultCellStyle.BackColor = Color.LightGray;

                Update_Screen();   //initial screen call
                this.Activate();    //activate screen
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error:  " + ex.Message);
            }
            return;
        }

        private void Update_Screen()    //Takes user input from tool strip variables and starts/updates the query, screen, and timers
        {
            try
            {
                double f = Convert.ToDouble(cmbFont.Text);  //screen selected font
                float fs = font_size;  //current font
                site = cbSite.Text;
                refresh_minutes = Convert.ToInt32(cmbRefreshRate.Text);  //get refresh minutes
                int refresh_miliseconds = (refresh_minutes * 60) * 1000;
                weeksBefore = Convert.ToInt32(cbWeeksBefore.Text);
                weeksAfter = Convert.ToInt32(cbWeeksAfter.Text);
                Days = Convert.ToInt32(cbDays.Text);
                using (SqlConnection objConn = new SqlConnection(strConnection))
                {
                    objConn.Open();

                    SqlCommand cmd = new SqlCommand("BigAssFans.dbo.spPOMaterialShortages", objConn);
                    cmd.CommandType = CommandType.StoredProcedure;
                    cmd.CommandTimeout = 1200;

                    SqlDataAdapter sdaAppScreen = new SqlDataAdapter(cmd);

                    cmd.Parameters.AddWithValue("@Site", site);
                    cmd.Parameters.AddWithValue("@Days", Days);
                    cmd.Parameters.AddWithValue("@WeeksBefore", weeksBefore);
                    cmd.Parameters.AddWithValue("@WeeksAfter", weeksAfter);
                    RefreshTimer.Interval = refresh_miliseconds;         
                    DataSet dsAppScreen = new DataSet();
                    sdaAppScreen.Fill(dsAppScreen);
                    dsAppScreen.Tables[0].Columns["name"].SetOrdinal(0);
                    dgvAppScreen.DataSource = dsAppScreen.Tables[0];
                    dgvAppScreen2.DataSource = dsAppScreen.Tables[0];

                    int range = (int)((width - 800) / 100);

                    switch(range)  //sets default column widths and font based on screen width 800 and above
                    {
                        #region Width: 800 to 899
                        case 0:
                            splitContainer1.SplitterDistance = (int)(0.17 * width);
                            font_size = (float)12;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 139;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 63;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 63;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 43;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 83;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 64;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 28;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 28;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 139;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 267;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 124;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 179;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 94;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 94;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 94;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 216;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 900 to 999
                        case 1:
                            splitContainer1.SplitterDistance = (int)(0.18 * width);
                            font_size = (float)13;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 141;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 65;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 65;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 45;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 85;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 66;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 30;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 30;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 141;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 268;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 126;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 181;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 96;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 96;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 96;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 217;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1000 to 1099
                        case 2:
                            splitContainer1.SplitterDistance = (int)(0.18 * width);
                            font_size = (float)13.5;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 143;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 68;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 68;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 50;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 96;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 68;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 32;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 32;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 143;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 269;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 128;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 183;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 98;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 98;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 98;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 218;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1100 to 1199
                        case 3:
                            splitContainer1.SplitterDistance = (int)(0.19 * width);
                            font_size = (float)14;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 145;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 70;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 70;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 52;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 98;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 70;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 34;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 34;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 145;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 270;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 130;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 185;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 100;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 100;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 100;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 219;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1200 to 1299
                        case 4:
                            splitContainer1.SplitterDistance = (int)(0.19 * width);
                            font_size = (float)14.5;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 147;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 72;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 72;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 54;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 100;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 72;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 36;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 36;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 147;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 271;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 132;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 187;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 102;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 102;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 102;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 220;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1300 to 1399
                        case 5:
                            splitContainer1.SplitterDistance = (int)(0.19 * width); 
                            font_size = (float)15;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 149;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 74;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 74;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 56;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 102;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 74;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 38;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 38;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 149;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 272;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 134;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 189;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 104;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 104;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 104;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 221;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1400 to 1499
                        case 6:
                            font_size = (float)15.5;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 151;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 76;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 76;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 58;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 104;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 76;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 40;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 40;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 151;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 273;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 136;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 191;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 106;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 106;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 106;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 222;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1500 to 1599
                        case 7:
                            font_size = (float)16;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 153;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 78;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 78;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 60;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 106;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }


                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 78;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 42;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 42;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 153;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 274;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 138;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 193;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 108;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 108;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 108;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 223;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                            break;
                        #endregion

                        #region Width: 1600 to 1699     //verified
                        case 8:
                            font_size = (float)17;
                            foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 155;
                                        break;
                                    //case "QtyA":
                                    //    dc.HeaderText = "Qty A";
                                    //    dc.Width = 80;
                                    //    break;
                                    //case "qtyB":
                                    //    dc.HeaderText = "Qty B";
                                    //    dc.Width = 80;
                                    //    break;
                                    case "qtyC":
                                        dc.HeaderText = "Qty C";
                                        dc.DefaultCellStyle.Format = "N0";
                                        dc.Width = 62;
                                        break;
                                    case "JobDueDate":
                                        dc.HeaderText = "Job Due Date";
                                        dc.Width = 108;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }

                    
                            foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                            {
                                switch (dc.Name)
                                {
                                    case "num2":
                                        dc.HeaderText = "Number 2";
                                        dc.Width = 80;
                                        break;
                                    case "num3":
                                        dc.HeaderText = "Number 3";
                                        dc.Width = 44;
                                        break;
                                    case "num4":
                                        dc.HeaderText = "Number 4";
                                        dc.Width = 45;
                                        break;
                                    case "num":
                                        dc.HeaderText = "Number";
                                        dc.Width = 155;
                                        break;
                                    case "numdescription":
                                        dc.HeaderText = "Description";
                                        dc.MinimumWidth = 275;
                                        break;
                                    case "class":
                                        dc.HeaderText = "Class";
                                        dc.Width = 140;
                                        break;
                                    case "name":
                                        dc.HeaderText = "Name";
                                        dc.Width = 195;
                                        break;
                                    case "date1":
                                        dc.HeaderText = "Date 1";
                                        dc.Width = 110;
                                        break;
                                    //case "promisedt":
                                    //    dc.HeaderText = "Promise Date";
                                    //    dc.Width = 100;
                                    //    break;
                                    case "date2":
                                        dc.HeaderText = "Date 2";
                                        dc.Width = 110;
                                        break;
                                    case "comment":
                                        dc.HeaderText = "Comment";
                                        dc.MinimumWidth = 225;
                                        break;
                                    default:
                                        dc.Visible = false;
                                        break;
                                }
                            }
                        break;
                        #endregion

                        #region Width: 1700 to 1799
                        case 9:
                        font_size = (float)18;
                        foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 180;
                                    break;
                                //case "QtyA":
                                //    dc.HeaderText = "Qty A";
                                //    dc.Width = 80;
                                //    break;
                                //case "qtyB":
                                //    dc.HeaderText = "Qty B";
                                //    dc.Width = 80;
                                //    break;
                                case "qtyC":
                                    dc.HeaderText = "Qty C";
                                    dc.DefaultCellStyle.Format = "N0";
                                    dc.Width = 70;
                                    break;
                                case "JobDueDate":
                                    dc.HeaderText = "Job Due Date";
                                    dc.Width = 113;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }


                        foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num2":
                                    dc.HeaderText = "Number 2";
                                    dc.Width = 85;
                                    break;
                                case "num3":
                                    dc.HeaderText = "Number 3";
                                    dc.Width = 47;
                                    break;
                                case "num4":
                                    dc.HeaderText = "Number 4";
                                    dc.Width = 47;
                                    break;
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 185;
                                    break;
                                case "numdescription":
                                    dc.HeaderText = "Description";
                                    dc.MinimumWidth = 292;
                                    break;
                                case "class":
                                    dc.HeaderText = "Class";
                                    dc.Width = 167;
                                    break;
                                case "name":
                                    dc.HeaderText = "Name";
                                    dc.Width = 197;
                                    break;
                                case "date1":
                                    dc.HeaderText = "Date 1";
                                    dc.Width = 113;
                                    break;
                                //case "promisedt":
                                //    dc.HeaderText = "Promise Date";
                                //    dc.Width = 100;
                                //    break;
                                case "date2":
                                    dc.HeaderText = "Date 2";
                                    dc.Width = 113;
                                    break;
                                case "comment":
                                    dc.HeaderText = "Comment";
                                    dc.MinimumWidth = 235;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }
                        break;
                        #endregion

                        #region Width: 1800 to 1899
                        case 10:
                        font_size = (float)18.5;
                        foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 195;
                                    break;
                                //case "QtyA":
                                //    dc.HeaderText = "Qty A";
                                //    dc.Width = 80;
                                //    break;
                                //case "qtyB":
                                //    dc.HeaderText = "Qty B";
                                //    dc.Width = 80;
                                //    break;
                                case "qtyC":
                                    dc.HeaderText = "Qty C";
                                    dc.DefaultCellStyle.Format = "N0";
                                    dc.Width = 75;
                                    break;
                                case "JobDueDate":
                                    dc.HeaderText = "Job Due Date";
                                    dc.Width = 117;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }


                        foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num2":
                                    dc.HeaderText = "Number 2";
                                    dc.Width = 87;
                                    break;
                                case "num3":
                                    dc.HeaderText = "Number 3";
                                    dc.Width = 48;
                                    break;
                                case "num4":
                                    dc.HeaderText = "Number 4";
                                    dc.Width = 48;
                                    break;
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 187;
                                    break;
                                case "numdescription":
                                    dc.HeaderText = "Description";
                                    dc.MinimumWidth = 295;
                                    break;
                                case "class":
                                    dc.HeaderText = "Class";
                                    dc.Width = 168;
                                    break;
                                case "name":
                                    dc.HeaderText = "Name";
                                    dc.Width = 198;
                                    break;
                                case "date1":
                                    dc.HeaderText = "Date 1";
                                    dc.Width = 117;
                                    break;
                                //case "promisedt":
                                //    dc.HeaderText = "Promise Date";
                                //    dc.Width = 100;
                                //    break;
                                case "date2":
                                    dc.HeaderText = "Date 2";
                                    dc.Width = 117;
                                    break;
                                case "comment":
                                    dc.HeaderText = "Comment";
                                    dc.MinimumWidth = 240;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }
                        break;
                        #endregion

                        #region Width: 1900 to 1999     //verified
                        case 11:
                        splitContainer1.SplitterDistance = (int)(0.2 * width);
                        font_size = (float)19;
                        foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 195;
                                    break;
                                //case "QtyA":
                                //    dc.HeaderText = "Qty A";
                                //    dc.Width = 80;
                                //    break;
                                //case "qtyB":
                                //    dc.HeaderText = "Qty B";
                                //    dc.Width = 80;
                                //    break;
                                case "qtyC":
                                    dc.HeaderText = "Qty C";
                                    dc.DefaultCellStyle.Format = "N0";
                                    dc.Width = 65;
                                    break;
                                case "JobDueDate":
                                    dc.HeaderText = "Job Due Date";
                                    dc.Width = 125;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }

                    
                        foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num2":
                                    dc.HeaderText = "Number 2";
                                    dc.Width = 90;
                                    break;
                                case "num3":
                                    dc.HeaderText = "Number 3";
                                    dc.Width = 50;
                                    break;
                                case "num4":
                                    dc.HeaderText = "Number 4";
                                    dc.Width = 50;
                                    break;
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 195;
                                    break;
                                case "numdescription":
                                    dc.HeaderText = "Description";
                                    dc.MinimumWidth = 300;
                                    break;
                                case "class":
                                    dc.HeaderText = "Class";
                                    dc.Width = 175;
                                    break;
                                case "name":
                                    dc.HeaderText = "Name";
                                    dc.Width = 200;
                                    break;
                                case "date1":
                                    dc.HeaderText = "Date 1";
                                    dc.Width = 125;
                                    break;
                                //case "promisedt":
                                //    dc.HeaderText = "Promise Date";
                                //    dc.Width = 100;
                                //    break;
                                case "date2":
                                    dc.HeaderText = "Date 2";
                                    dc.Width = 125;
                                    break;
                                case "comment":
                                    dc.HeaderText = "Comment";
                                    dc.MinimumWidth = 250;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }
                        break;
                        #endregion

                        #region Width: 2000 and up 
                        default:
                        splitContainer1.SplitterDistance = (int)(0.22 * width);
                        font_size = (float)20;
                        foreach (DataGridViewColumn dc in dgvAppScreen.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 200;
                                    break;
                                //case "QtyA":
                                //    dc.HeaderText = "Qty A";
                                //    dc.Width = 80;
                                //    break;
                                //case "qtyB":
                                //    dc.HeaderText = "Qty B";
                                //    dc.Width = 80;
                                //    break;
                                case "qtyC":
                                    dc.HeaderText = "Qty C";
                                    dc.DefaultCellStyle.Format = "N0";
                                    dc.Width = 85;
                                    break;
                                case "JobDueDate":
                                    dc.HeaderText = "Job Due Date";
                                    dc.Width = 130;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }


                        foreach (DataGridViewColumn dc in dgvAppScreen2.Columns)
                        {
                            switch (dc.Name)
                            {
                                case "num2":
                                    dc.HeaderText = "Number 2";
                                    dc.Width = 95;
                                    break;
                                case "num3":
                                    dc.HeaderText = "Number 3";
                                    dc.Width = 55;
                                    break;
                                case "num4":
                                    dc.HeaderText = "Number 4";
                                    dc.Width = 55;
                                    break;
                                case "num":
                                    dc.HeaderText = "Number";
                                    dc.Width = 200;
                                    break;
                                case "numdescription":
                                    dc.HeaderText = "Description";
                                    dc.MinimumWidth = 305;
                                    break;
                                case "class":
                                    dc.HeaderText = "Class";
                                    dc.Width = 180;
                                    break;
                                case "name":
                                    dc.HeaderText = "Name";
                                    dc.Width = 205;
                                    break;
                                case "date1":
                                    dc.HeaderText = "Date 1";
                                    dc.Width = 130;
                                    break;
                                //case "promisedt":
                                //    dc.HeaderText = "Promise Date";
                                //    dc.Width = 100;
                                //    break;
                                case "date2":
                                    dc.HeaderText = "Date 2";
                                    dc.Width = 130;
                                    break;
                                case "comment":
                                    dc.HeaderText = "Comment";
                                    dc.MinimumWidth = 255;
                                    break;
                                default:
                                    dc.Visible = false;
                                    break;
                            }
                        }
                        break;
                        #endregion
                    }
                    if(first_update)   //check if first time the screen has been updated (initial display)
                    {
                        first_update = false;    //if so, then set first_update to false for subsequent updates
                    }
                    else
                    { 
                            font_size = (float)f;       //if not, then this over-rides the preset fontsize for that screen size in case changed by user.
                    }
                    splitContainer1.Font = new Font(splitContainer1.Font.FontFamily, font_size);  //execute font size changes

                    //dgvAppScreen.AutoResizeColumns();
                    //dgvAppScreen2.AutoResizeColumns();
                    dgvAppScreen.Update();
                    dgvAppScreen2.Update();
                    this.Show();
                    RefreshTimer.Start();  //start timers
                    ScrollTimer.Start();
                }
            }
            catch (Exception e)
            {
                throw (e);
                try
                {
                    this.Close();
                }
                catch (Exception close_error)
                {
                    MessageBox.Show("Error closing windows form:  " + close_error);
                }
            }
            return;
        }

        private void btnExit_Click(object sender, EventArgs e)
        {   //stop timers, close, and exit app
            try
            {
                RefreshTimer.Stop();
                ScrollTimer.Stop();
                this.Close();
            }
            catch (Exception EX)
            {
                MessageBox.Show("Error on Exit:  " + EX.Message);
            }
            return;
        }

        private void RefreshTimer_Tick(object sender, EventArgs e)
        {   //stop timers, update screen, then restart the timers fresh
            try
            {
                RefreshTimer.Stop();
                ScrollTimer.Stop();
                Update_Screen();
            }
            catch (Exception exc)
            {
                MessageBox.Show("Refresh Timer Error:  " + exc.Message);
            }
            return;
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {   //stop timers, update screen, then restart the timers fresh
            try
            {
                RefreshTimer.Stop();
                ScrollTimer.Stop();
                Update_Screen();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Refresh Error:  " + ex.Message);
            }
            return;
        }

        private void ScrollTimer_Tick(object sender, EventArgs e)
        {   //stop scrolling timer, reset to top, then start scrolling timer
            try
            {
                ScrollTimer.Stop();
                foreach (Control ctl in this.dgvAppScreen.Controls)  //check if App Screen data set is scrollable
                {
                    if (ctl is VScrollBar)
                    {
                        VScrollBar scroll = (VScrollBar)ctl;
                        if (scroll.Visible)
                            AppScreenScroll = true;
                        else
                            AppScreenScroll = false;
                    }
                }
                foreach (Control ctrl in this.dgvAppScreen2.Controls)  //check if App Screen 2 data set is scrollable
                {
                    if (ctrl is VScrollBar)
                    {
                        VScrollBar scrolling = (VScrollBar)ctrl;
                        if (scrolling.Visible)
                            AppScreen2Scroll = true;
                        else
                            AppScreen2Scroll = false;
                    }
                }
                if (AppScreenScroll)
                {
                    if (this.dgvAppScreen.FirstDisplayedScrollingRowIndex == previous1)  //check if screen scroll is at bottom of the set
                        bottom = true;
                    if (this.dgvAppScreen.FirstDisplayedScrollingRowIndex < this.dgvAppScreen.Rows.Count)     //if not at end of set, scroll down.
                    {
                        previous1 = this.dgvAppScreen.FirstDisplayedScrollingRowIndex;
                        this.dgvAppScreen.FirstDisplayedScrollingRowIndex = this.dgvAppScreen.FirstDisplayedScrollingRowIndex + 1;
                        previous2 = this.dgvAppScreen2.FirstDisplayedScrollingRowIndex;
                        this.dgvAppScreen2.FirstDisplayedScrollingRowIndex = this.dgvAppScreen2.FirstDisplayedScrollingRowIndex + 1;
                    }
                    if (bottom)   //if is at end of set, reset scroll to beginning of the set
                    {
                        this.dgvAppScreen.FirstDisplayedScrollingRowIndex = 0;
                        this.dgvAppScreen2.FirstDisplayedScrollingRowIndex = 0;
                        bottom = false;
                        previous1 = -1;
                        previous2 = -1;
                    }
                }
                ScrollTimer.Start();
            }
            catch (Exception EX)
            {
                MessageBox.Show("Scroll Timer Error:  " + EX.Message);
            }
            return;
        }
    }
}