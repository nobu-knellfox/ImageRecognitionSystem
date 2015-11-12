using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace ImageRecognitionSystem
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {

        private OpenFileDialog screen_ofd;
        private OpenFileDialog template_ofd;

        ImageRecognitionSystemCpp.ImageRecognition recog = new ImageRecognitionSystemCpp.ImageRecognition();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Screen_Click(object sender, RoutedEventArgs e)
        {
            screen_ofd = new OpenFileDialog();
            screen_ofd.FileName = "";
            screen_ofd.DefaultExt = "*.*";
            screen_ofd.ShowDialog();
        }

        private void Template_Click(object sender, RoutedEventArgs e)
        {
            template_ofd = new OpenFileDialog();
            template_ofd.FileName = "";
            template_ofd.DefaultExt = "*.*";
            template_ofd.ShowDialog();
        }

        private void Recognition_Click(object sender, RoutedEventArgs e)
        {
            recog.Recognition(screen_ofd.FileName,template_ofd.FileName);
        }
    }
}
