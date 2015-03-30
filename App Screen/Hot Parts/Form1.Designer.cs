//Nick Hollis 2014
//This cs file is for the design and control of the screen itself using a windows form
//including auto-scrolling functionality if the page is longer than screen
namespace App_Screen
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.dgvAppScreen = new System.Windows.Forms.DataGridView();
            this.dgvAppScreen2 = new System.Windows.Forms.DataGridView();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.lblSite = new System.Windows.Forms.ToolStripLabel();
            this.cbSite = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.lblWeeksBefore = new System.Windows.Forms.ToolStripLabel();
            this.cbWeeksBefore = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.lblWeeksAfter = new System.Windows.Forms.ToolStripLabel();
            this.cbWeeksAfter = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.lblDays = new System.Windows.Forms.ToolStripLabel();
            this.cbDays = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.btnExit = new System.Windows.Forms.ToolStripButton();
            this.lblRefreshRate = new System.Windows.Forms.ToolStripLabel();
            this.cmbRefreshRate = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.lblFont = new System.Windows.Forms.ToolStripLabel();
            this.cmbFont = new System.Windows.Forms.ToolStripComboBox();
            this.btnRefresh = new System.Windows.Forms.ToolStripButton();
            this.RefreshTimer = new System.Windows.Forms.Timer(this.components);
            this.ScrollTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAppScreen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAppScreen2)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F);
            this.splitContainer1.Location = new System.Drawing.Point(0, 28);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.dgvAppScreen);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.dgvAppScreen2);
            this.splitContainer1.Size = new System.Drawing.Size(1184, 734);
            this.splitContainer1.SplitterDistance = 268;
            this.splitContainer1.TabIndex = 1;
            // 
            // dgvAppScreen
            // 
            this.dgvAppScreen.AllowUserToAddRows = false;
            this.dgvAppScreen.AllowUserToDeleteRows = false;
            this.dgvAppScreen.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dgvAppScreen.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgvAppScreen.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvAppScreen.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvAppScreen.Location = new System.Drawing.Point(0, 0);
            this.dgvAppScreen.Name = "dgvAppScreen";
            this.dgvAppScreen.ReadOnly = true;
            this.dgvAppScreen.Size = new System.Drawing.Size(268, 734);
            this.dgvAppScreen.TabIndex = 0;
            // 
            // dgvAppScreen2
            // 
            this.dgvAppScreen2.AllowUserToAddRows = false;
            this.dgvAppScreen2.AllowUserToDeleteRows = false;
            this.dgvAppScreen2.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dgvAppScreen2.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgvAppScreen2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvAppScreen2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvAppScreen2.Location = new System.Drawing.Point(0, 0);
            this.dgvAppScreen2.Name = "dgvAppScreen2";
            this.dgvAppScreen2.ReadOnly = true;
            this.dgvAppScreen2.Size = new System.Drawing.Size(912, 734);
            this.dgvAppScreen2.TabIndex = 1;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lblSite,
            this.cbSite,
            this.toolStripSeparator1,
            this.lblWeeksBefore,
            this.cbWeeksBefore,
            this.toolStripSeparator4,
            this.lblWeeksAfter,
            this.cbWeeksAfter,
            this.toolStripSeparator5,
            this.lblDays,
            this.cbDays,
            this.toolStripSeparator2,
            this.btnExit,
            this.lblRefreshRate,
            this.cmbRefreshRate,
            this.toolStripSeparator3,
            this.lblFont,
            this.cmbFont,
            this.btnRefresh});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1184, 27);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "App Screen";
            // 
            // lblSite
            // 
            this.lblSite.Name = "lblSite";
            this.lblSite.Size = new System.Drawing.Size(37, 24);
            this.lblSite.Text = "Site:";
            // 
            // cbSite
            // 
            this.cbSite.Items.AddRange(new object[] {
            "Site1",
            "Site2",
            "Site3"});
            this.cbSite.Name = "cbSite";
            this.cbSite.Size = new System.Drawing.Size(85, 27);
            this.cbSite.Text = "Site1";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // lblWeeksBefore
            // 
            this.lblWeeksBefore.Name = "lblWeeksBefore";
            this.lblWeeksBefore.Size = new System.Drawing.Size(112, 24);
            this.lblWeeksBefore.Text = "Weeks Before:";
            // 
            // cbWeeksBefore
            // 
            this.cbWeeksBefore.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cbWeeksBefore.Name = "cbWeeksBefore";
            this.cbWeeksBefore.Size = new System.Drawing.Size(75, 27);
            this.cbWeeksBefore.Text = "4";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 27);
            // 
            // lblWeeksAfter
            // 
            this.lblWeeksAfter.Name = "lblWeeksAfter";
            this.lblWeeksAfter.Size = new System.Drawing.Size(110, 24);
            this.lblWeeksAfter.Text = "Weeks After:";
            // 
            // cbWeeksAfter
            // 
            this.cbWeeksAfter.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cbWeeksAfter.Name = "cbWeeksAfter";
            this.cbWeeksAfter.Size = new System.Drawing.Size(75, 27);
            this.cbWeeksAfter.Text = "2";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 27);
            // 
            // lblDays
            // 
            this.lblDays.Name = "lblDays";
            this.lblDays.Size = new System.Drawing.Size(135, 24);
            this.lblDays.Text = "Days Out:";
            // 
            // cbDays
            // 
            this.cbDays.DropDownWidth = 75;
            this.cbDays.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15"});
            this.cbDays.Name = "cbDays";
            this.cbDays.Size = new System.Drawing.Size(75, 27);
            this.cbDays.Text = "10";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Margin = new System.Windows.Forms.Padding(30, 0, 30, 0);
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 27);
            // 
            // btnExit
            // 
            this.btnExit.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.btnExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.btnExit.Image = ((System.Drawing.Image)(resources.GetObject("btnExit.Image")));
            this.btnExit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnExit.Name = "btnExit";
            this.btnExit.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.btnExit.Padding = new System.Windows.Forms.Padding(8, 0, 0, 0);
            this.btnExit.Size = new System.Drawing.Size(42, 24);
            this.btnExit.Text = "EXIT";
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // lblRefreshRate
            // 
            this.lblRefreshRate.Name = "lblRefreshRate";
            this.lblRefreshRate.Size = new System.Drawing.Size(142, 24);
            this.lblRefreshRate.Text = "Refresh Rate (in minutes):";
            // 
            // cmbRefreshRate
            // 
            this.cmbRefreshRate.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.cmbRefreshRate.Name = "cmbRefreshRate";
            this.cmbRefreshRate.Padding = new System.Windows.Forms.Padding(0, 0, 10, 0);
            this.cmbRefreshRate.Size = new System.Drawing.Size(75, 27);
            this.cmbRefreshRate.Text = "2";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 27);
            // 
            // lblFont
            // 
            this.lblFont.Name = "lblFont";
            this.lblFont.Size = new System.Drawing.Size(31, 24);
            this.lblFont.Text = "Font";
            // 
            // cmbFont
            // 
            this.cmbFont.DropDownWidth = 65;
            this.cmbFont.Items.AddRange(new object[] {
            "7.0",
            "7.5",
            "8.0",
            "8.5",
            "9.0",
            "9.5",
            "10",
            "10.5",
            "11",
            "11.5",
            "12",
            "12.5",
            "13",
            "13.5",
            "14",
            "14.5",
            "15",
            "15.5",
            "16",
            "16.5",
            "17",
            "17.5",
            "18",
            "18.5",
            "19",
            "19.5",
            "20",
            "20.5",
            "21",
            "21.5",
            "22",
            "22.5",
            "23",
            "23.5",
            "24",
            "24.5",
            "25",
            "25.5",
            "26"});
            this.cmbFont.Name = "cmbFont";
            this.cmbFont.Size = new System.Drawing.Size(75, 23);
            this.cmbFont.Text = "19";
            // 
            // btnRefresh
            // 
            this.btnRefresh.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.btnRefresh.Image = ((System.Drawing.Image)(resources.GetObject("btnRefresh.Image")));
            this.btnRefresh.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Padding = new System.Windows.Forms.Padding(8, 0, 0, 0);
            this.btnRefresh.Size = new System.Drawing.Size(58, 19);
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // RefreshTimer
            // 
            this.RefreshTimer.Interval = 120000;
            this.RefreshTimer.Tick += new System.EventHandler(this.RefreshTimer_Tick);
            // 
            // ScrollTimer
            // 
            this.ScrollTimer.Interval = 2000;
            this.ScrollTimer.Tick += new System.EventHandler(this.ScrollTimer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1184, 762);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.splitContainer1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "App Screen Screen";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvAppScreen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvAppScreen2)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.DataGridView dgvAppScreen;
        private System.Windows.Forms.DataGridView dgvAppScreen2;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripLabel lblSite;
        private System.Windows.Forms.ToolStripComboBox cbSite;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripLabel lblWeeksBefore;
        private System.Windows.Forms.ToolStripComboBox cbWeeksBefore;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripLabel lblWeeksAfter;
        private System.Windows.Forms.ToolStripComboBox cbWeeksAfter;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripLabel lblDays;
        private System.Windows.Forms.ToolStripComboBox cbDays;
        private System.Windows.Forms.ToolStripButton btnExit;
        private System.Windows.Forms.ToolStripButton btnRefresh;
        private System.Windows.Forms.Timer RefreshTimer;
        private System.Windows.Forms.Timer ScrollTimer;
        private System.Windows.Forms.ToolStripLabel lblRefreshRate;
        private System.Windows.Forms.ToolStripComboBox cmbRefreshRate;
        private System.Windows.Forms.ToolStripLabel lblFont;
        private System.Windows.Forms.ToolStripComboBox cmbFont;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
    }
}

