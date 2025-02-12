namespace Perceptron
{
    partial class frmMain
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
            this.btnLearn = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.trackLearningRate = new System.Windows.Forms.TrackBar();
            this.lblLearningRate = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtIterations = new System.Windows.Forms.TextBox();
            this.pnlCanvas = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.trackLearningRate)).BeginInit();
            this.SuspendLayout();
            // 
            // btnLearn
            // 
            this.btnLearn.Location = new System.Drawing.Point(218, 160);
            this.btnLearn.Name = "btnLearn";
            this.btnLearn.Size = new System.Drawing.Size(142, 23);
            this.btnLearn.TabIndex = 1;
            this.btnLearn.Text = "Learn";
            this.btnLearn.UseVisualStyleBackColor = true;
            this.btnLearn.Click += new System.EventHandler(this.btnLearn_Click);
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(218, 189);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(142, 23);
            this.btnClear.TabIndex = 2;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // trackLearningRate
            // 
            this.trackLearningRate.Location = new System.Drawing.Point(218, 46);
            this.trackLearningRate.Maximum = 500;
            this.trackLearningRate.Name = "trackLearningRate";
            this.trackLearningRate.Size = new System.Drawing.Size(141, 45);
            this.trackLearningRate.TabIndex = 3;
            this.trackLearningRate.TickFrequency = 20;
            this.trackLearningRate.Scroll += new System.EventHandler(this.trackLearningRate_Scroll);
            // 
            // lblLearningRate
            // 
            this.lblLearningRate.Location = new System.Drawing.Point(218, 20);
            this.lblLearningRate.Name = "lblLearningRate";
            this.lblLearningRate.Size = new System.Drawing.Size(142, 23);
            this.lblLearningRate.TabIndex = 4;
            this.lblLearningRate.Text = "Learning Rate: 0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(218, 88);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Number of Iterations:";
            // 
            // txtIterations
            // 
            this.txtIterations.Location = new System.Drawing.Point(318, 85);
            this.txtIterations.Name = "txtIterations";
            this.txtIterations.Size = new System.Drawing.Size(42, 20);
            this.txtIterations.TabIndex = 6;
            this.txtIterations.Text = "100";
            // 
            // pnlCanvas
            // 
            this.pnlCanvas.BackColor = System.Drawing.Color.White;
            this.pnlCanvas.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlCanvas.Location = new System.Drawing.Point(12, 12);
            this.pnlCanvas.Name = "pnlCanvas";
            this.pnlCanvas.Size = new System.Drawing.Size(200, 200);
            this.pnlCanvas.TabIndex = 7;
            this.pnlCanvas.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlCanvas_Paint);
            this.pnlCanvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnlCanvas_MouseDown);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(372, 231);
            this.Controls.Add(this.pnlCanvas);
            this.Controls.Add(this.txtIterations);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblLearningRate);
            this.Controls.Add(this.trackLearningRate);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnLearn);
            this.Name = "frmMain";
            this.Text = "Perceptron Simulation";
            this.Load += new System.EventHandler(this.frmMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackLearningRate)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnLearn;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.TrackBar trackLearningRate;
        private System.Windows.Forms.Label lblLearningRate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtIterations;
        private System.Windows.Forms.Panel pnlCanvas;
    }
}

