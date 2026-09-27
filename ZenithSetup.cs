using System;
using System.IO;
using System.IO.Compression;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;
using Microsoft.Win32;
using System.Diagnostics;

namespace ZenithLauncher.Installer
{
    public class SetupForm : Form
    {
        private Label lblTitle;
        private Label lblSubtitle;
        private Label lblPath;
        private TextBox txtPath;
        private Button btnBrowse;
        private CheckBox chkDesktop;
        private CheckBox chkStartMenu;
        private ProgressBar progressBar;
        private Label lblStatus;
        private Button btnAction;
        private bool isFinished = false;

        public SetupForm()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.Text = "Zenith Launcher Setup";
            this.Size = new Size(620, 440);
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.FromArgb(13, 15, 23);
            this.ForeColor = Color.FromArgb(230, 237, 243);
            this.Font = new Font("Segoe UI", 9.5f, FontStyle.Regular);

            // Icon
            try {
                this.Icon = Icon.ExtractAssociatedIcon(Assembly.GetExecutingAssembly().Location);
            } catch {}

            // Header Panel
            Panel headerPanel = new Panel();
            headerPanel.Dock = DockStyle.Top;
            headerPanel.Height = 85;
            headerPanel.BackColor = Color.FromArgb(10, 11, 17);
            this.Controls.Add(headerPanel);

            lblTitle = new Label();
            lblTitle.Text = "⚡ ZENITH LAUNCHER";
            lblTitle.Font = new Font("Segoe UI", 18f, FontStyle.Bold);
            lblTitle.ForeColor = Color.FromArgb(0, 255, 204);
            lblTitle.Location = new Point(25, 14);
            lblTitle.AutoSize = true;
            headerPanel.Controls.Add(lblTitle);

            lblSubtitle = new Label();
            lblSubtitle.Text = "Next-Generation Minecraft Launcher (Cyber Edition)";
            lblSubtitle.Font = new Font("Segoe UI", 9.5f, FontStyle.Regular);
            lblSubtitle.ForeColor = Color.FromArgb(139, 148, 158);
            lblSubtitle.Location = new Point(27, 48);
            lblSubtitle.AutoSize = true;
            headerPanel.Controls.Add(lblSubtitle);

            // Content
            lblPath = new Label();
            lblPath.Text = "Destination Folder:";
            lblPath.Location = new Point(25, 105);
            lblPath.AutoSize = true;
            this.Controls.Add(lblPath);

            txtPath = new TextBox();
            string defaultDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Programs", "ZenithLauncher");
            txtPath.Text = defaultDir;
            txtPath.Location = new Point(28, 130);
            txtPath.Size = new Size(450, 28);
            txtPath.BackColor = Color.FromArgb(22, 27, 38);
            txtPath.ForeColor = Color.White;
            txtPath.BorderStyle = BorderStyle.FixedSingle;
            this.Controls.Add(txtPath);

            btnBrowse = new Button();
            btnBrowse.Text = "Browse...";
            btnBrowse.Location = new Point(488, 128);
            btnBrowse.Size = new Size(95, 30);
            btnBrowse.BackColor = Color.FromArgb(30, 38, 54);
            btnBrowse.ForeColor = Color.FromArgb(0, 255, 204);
            btnBrowse.FlatStyle = FlatStyle.Flat;
            btnBrowse.FlatAppearance.BorderColor = Color.FromArgb(44, 56, 78);
            btnBrowse.Click += (s, e) => {
                using (FolderBrowserDialog fbd = new FolderBrowserDialog()) {
                    fbd.SelectedPath = txtPath.Text;
                    if (fbd.ShowDialog() == DialogResult.OK) {
                        txtPath.Text = fbd.SelectedPath;
                    }
                }
            };
            this.Controls.Add(btnBrowse);

            chkDesktop = new CheckBox();
            chkDesktop.Text = "Create Desktop Shortcut";
            chkDesktop.Checked = true;
            chkDesktop.Location = new Point(28, 175);
            chkDesktop.AutoSize = true;
            chkDesktop.ForeColor = Color.FromArgb(200, 210, 220);
            this.Controls.Add(chkDesktop);

            chkStartMenu = new CheckBox();
            chkStartMenu.Text = "Create Start Menu Shortcut";
            chkStartMenu.Checked = true;
            chkStartMenu.Location = new Point(28, 205);
            chkStartMenu.AutoSize = true;
            chkStartMenu.ForeColor = Color.FromArgb(200, 210, 220);
            this.Controls.Add(chkStartMenu);

            lblStatus = new Label();
            lblStatus.Text = "Ready to install. Click Install to begin.";
            lblStatus.Location = new Point(25, 255);
            lblStatus.Size = new Size(550, 22);
            lblStatus.ForeColor = Color.FromArgb(139, 148, 158);
            this.Controls.Add(lblStatus);

            progressBar = new ProgressBar();
            progressBar.Location = new Point(28, 285);
            progressBar.Size = new Size(555, 22);
            progressBar.Style = ProgressBarStyle.Continuous;
            this.Controls.Add(progressBar);

            // Bottom Buttons
            btnAction = new Button();
            btnAction.Text = "INSTALL";
            btnAction.Font = new Font("Segoe UI", 10.5f, FontStyle.Bold);
            btnAction.Location = new Point(443, 335);
            btnAction.Size = new Size(140, 42);
            btnAction.BackColor = Color.FromArgb(0, 204, 163);
            btnAction.ForeColor = Color.FromArgb(10, 15, 20);
            btnAction.FlatStyle = FlatStyle.Flat;
            btnAction.FlatAppearance.BorderSize = 0;
            btnAction.Cursor = Cursors.Hand;
            btnAction.Click += BtnAction_Click;
            this.Controls.Add(btnAction);

            Button btnCancel = new Button();
            btnCancel.Text = "Cancel";
            btnCancel.Location = new Point(330, 335);
            btnCancel.Size = new Size(100, 42);
            btnCancel.BackColor = Color.FromArgb(25, 32, 45);
            btnCancel.ForeColor = Color.FromArgb(180, 190, 200);
            btnCancel.FlatStyle = FlatStyle.Flat;
            btnCancel.FlatAppearance.BorderColor = Color.FromArgb(44, 56, 78);
            btnCancel.Click += (s, e) => this.Close();
            this.Controls.Add(btnCancel);
        }

        private void BtnAction_Click(object sender, EventArgs e)
        {
            if (isFinished)
            {
                // Launch Launcher
                string targetDir = txtPath.Text;
                string exePath = Path.Combine(targetDir, "ZenithLauncher.exe");
                if (File.Exists(exePath))
                {
                    Process.Start(new ProcessStartInfo(exePath) { WorkingDirectory = targetDir });
                }
                this.Close();
                return;
            }

            btnAction.Enabled = false;
            txtPath.Enabled = false;
            btnBrowse.Enabled = false;
            chkDesktop.Enabled = false;
            chkStartMenu.Enabled = false;

            string dest = txtPath.Text;
            bool createDesktop = chkDesktop.Checked;
            bool createStart = chkStartMenu.Checked;

            Thread t = new Thread(() =>
            {
                try
                {
                    PerformInstall(dest, createDesktop, createStart);

                    this.Invoke((MethodInvoker)delegate
                    {
                        progressBar.Value = 100;
                        lblStatus.Text = "Installation completed successfully!";
                        lblStatus.ForeColor = Color.FromArgb(0, 255, 204);
                        btnAction.Text = "🚀 LAUNCH";
                        btnAction.BackColor = Color.FromArgb(0, 255, 204);
                        btnAction.Enabled = true;
                        isFinished = true;
                    });
                }
                catch (Exception ex)
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        lblStatus.Text = "Error: " + ex.Message;
                        lblStatus.ForeColor = Color.Salmon;
                        btnAction.Enabled = true;
                    });
                }
            });
            t.IsBackground = true;
            t.Start();
        }

        public static void PerformInstall(string destDir, bool createDesktop, bool createStartMenu)
        {
            if (!Directory.Exists(destDir))
            {
                Directory.CreateDirectory(destDir);
            }

            // Extract embedded payload
            Assembly asm = Assembly.GetExecutingAssembly();
            using (Stream s = asm.GetManifestResourceStream("ZenithPayload"))
            {
                if (s == null)
                {
                    throw new Exception("Embedded installation payload not found.");
                }
                using (ZipArchive archive = new ZipArchive(s))
                {
                    foreach (ZipArchiveEntry entry in archive.Entries)
                    {
                        string fullPath = Path.Combine(destDir, entry.FullName);
                        if (string.IsNullOrEmpty(entry.Name))
                        {
                            Directory.CreateDirectory(fullPath);
                            continue;
                        }

                        string parent = Path.GetDirectoryName(fullPath);
                        if (!Directory.Exists(parent))
                        {
                            Directory.CreateDirectory(parent);
                        }

                        entry.ExtractToFile(fullPath, true);
                    }
                }
            }

            // Copy self as Uninstall.exe
            string uninstallerPath = Path.Combine(destDir, "Uninstall.exe");
            try
            {
                File.Copy(Assembly.GetExecutingAssembly().Location, uninstallerPath, true);
            }
            catch {}

            string launcherExe = Path.Combine(destDir, "ZenithLauncher.exe");
            string iconPath = Path.Combine(destDir, "zenithlauncher.ico");
            if (!File.Exists(iconPath))
            {
                iconPath = launcherExe;
            }

            // Shortcuts via WScript.Shell
            Type shellType = Type.GetTypeFromProgID("WScript.Shell");
            if (shellType != null)
            {
                dynamic shell = Activator.CreateInstance(shellType);

                if (createDesktop)
                {
                    string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);
                    string lnk = Path.Combine(desktopPath, "Zenith Launcher.lnk");
                    dynamic shortcut = shell.CreateShortcut(lnk);
                    shortcut.TargetPath = launcherExe;
                    shortcut.WorkingDirectory = destDir;
                    shortcut.Description = "Zenith Launcher - Cyber Edition";
                    shortcut.IconLocation = iconPath + ",0";
                    shortcut.Save();
                }

                if (createStartMenu)
                {
                    string programsFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.StartMenu), "Programs");
                    string lnk = Path.Combine(programsFolder, "Zenith Launcher.lnk");
                    dynamic shortcut = shell.CreateShortcut(lnk);
                    shortcut.TargetPath = launcherExe;
                    shortcut.WorkingDirectory = destDir;
                    shortcut.Description = "Zenith Launcher - Cyber Edition";
                    shortcut.IconLocation = iconPath + ",0";
                    shortcut.Save();
                }
            }

            // Register in HKCU Uninstall
            try
            {
                using (RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Uninstall\ZenithLauncher"))
                {
                    if (key != null)
                    {
                        key.SetValue("DisplayName", "Zenith Launcher");
                        key.SetValue("DisplayVersion", "1.0.0");
                        key.SetValue("Publisher", "Zenith Team");
                        key.SetValue("DisplayIcon", iconPath);
                        key.SetValue("InstallLocation", destDir);
                        key.SetValue("UninstallString", "\"" + uninstallerPath + "\" /uninstall");
                        key.SetValue("NoModify", 1, RegistryValueKind.DWord);
                        key.SetValue("NoRepair", 1, RegistryValueKind.DWord);
                    }
                }
            }
            catch {}
        }

        public static void PerformUninstall()
        {
            DialogResult res = MessageBox.Show(
                "Are you sure you want to uninstall Zenith Launcher?",
                "Zenith Launcher Uninstall",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (res != DialogResult.Yes) return;

            string appDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

            // Remove Shortcuts
            try
            {
                string desktopLnk = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory), "Zenith Launcher.lnk");
                if (File.Exists(desktopLnk)) File.Delete(desktopLnk);

                string startLnk = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.StartMenu), "Programs", "Zenith Launcher.lnk");
                if (File.Exists(startLnk)) File.Delete(startLnk);
            }
            catch {}

            // Remove registry
            try
            {
                Registry.CurrentUser.DeleteSubKeyTree(@"Software\Microsoft\Windows\CurrentVersion\Uninstall\ZenithLauncher", false);
            }
            catch {}

            // Self-delete batch
            string batchPath = Path.Combine(Path.GetTempPath(), "zenith_uninst.bat");
            string batchContent = 
                "@echo off\r\n" +
                "timeout /t 2 /nobreak >nul\r\n" +
                "rmdir /s /q \"" + appDir + "\"\r\n" +
                "del \"%~f0\"\r\n";
            File.WriteAllText(batchPath, batchContent);

            Process.Start(new ProcessStartInfo(batchPath) {
                CreateNoWindow = true,
                UseShellExecute = false
            });

            MessageBox.Show("Zenith Launcher was uninstalled successfully.", "Zenith Launcher", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        [STAThread]
        public static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            if (args != null && args.Length > 0)
            {
                string cmd = args[0].ToLowerInvariant();
                if (cmd == "/uninstall" || cmd == "-uninstall" || cmd == "/uninst")
                {
                    PerformUninstall();
                    return;
                }
                if (cmd == "/s" || cmd == "/silent" || cmd == "-silent")
                {
                    string target = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Programs", "ZenithLauncher");
                    PerformInstall(target, true, true);
                    return;
                }
            }

            Application.Run(new SetupForm());
        }
    }
}
