using System;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace michomeframework.Scenaries
{
    /// <summary>
    /// Управление сценариями
    /// </summary>
    public class Scenes
    {
        public Gateway gtw;
        internal Scenes(Gateway g)
        {
            gtw = g;
        }

        /// <summary>
        /// Получает масиив всех сцен в сценарии
        /// </summary>
        /// <returns></returns>
        public SceneNode[] GetScenes()
        {
            List<SceneNode> ts = new List<SceneNode>();
            var apisc = gtw.SelectAPI("scenes.php?type=Select");
            JObject obj = JObject.Parse(apisc);
            for (int i = 0; i < obj["data"].Count(); i++)
            {
                var n = obj["data"][i];
                var starts = obj["times"]["start"].ToString();
                var starte = obj["times"]["end"].ToString();

                ts.Add(new SceneNode(n["ID"].Value<uint>(), n["Name"].ToString(), DateTime.Parse(n["TStart"].ToString()), DateTime.Parse(n["TEnd"].ToString()), n["Module"].ToString(), n["Data"].ToString(), n["NData"].ToString(), DateTime.Parse(n["CSE"].ToString()), n["Timeout"].Value<int>(), n["Enable"].ToString() == "1", starts, starte));
            }

            return ts.ToArray();
        }
        /// <summary>
        /// Сохраняет в сценариях данный сценарий
        /// </summary>
        /// <param name="node">Сцена</param>
        /// <returns></returns>
        public bool SetScene(SceneNode node)
        {
            return gtw.SelectAPI(String.Format("scenes.php?type=Edit&id={0}&name={1}&ts={2}&td={3}&module={4}&data={5}&ndata={6}&number={7}&timeout={8}&enable={9}", node.ID.ToString().Replace("&", "%26"), node.Name.Replace("&", "%26"), node.StartTime.TimeOfDay.ToString().Replace("&", "%26"), node.EndTime.TimeOfDay.ToString().Replace("&", "%26"), node.Modules.Replace("&", "%26"), node.SendThen.Replace("&", "%26"), node.SendEnd.Replace("&", "%26"), node.ID.ToString().Replace("&", "%26"), node.Timeout.ToString().Replace("&", "%26"), node.Enable.ToString().ToLower())) == "OK";
        }
        /// <summary>
        /// Сохраняет в сценариях данный сценарий
        /// </summary>
        /// <param name="node">Сцена</param>
        /// <returns></returns>
        public bool SetScene(SceneNode node, int newID)
        {
            return gtw.SelectAPI(String.Format("scenes.php?type=Edit&id={0}&name={1}&ts={2}&td={3}&module={4}&data={5}&ndata={6}&number={7}&timeout={8}&enable={9}", node.ID.ToString().Replace("&", "%26"), node.Name.Replace("&", "%26"), node.StartTime.TimeOfDay.ToString().Replace("&", "%26"), node.EndTime.TimeOfDay.ToString().Replace("&", "%26"), node.Modules.Replace("&", "%26"), node.SendThen.Replace("&", "%26"), node.SendEnd.Replace("&", "%26"), newID.ToString().Replace("&", "%26"), node.Timeout.ToString().Replace("&", "%26"), node.Enable.ToString().ToLower())) == "OK";
        }
        /// <summary>
        /// Сохраняет в сценариях данный массив сценарией
        /// </summary>
        /// <param name="node">Сцена</param>
        /// <returns></returns>
        public void SetScene(SceneNode[] node)
        {
            foreach (var item in node)
                SetScene(item);
        }
        /// <summary>
        /// Удаляет сцену из сценариев
        /// </summary>
        /// <param name="node">Сцена для удаления</param>
        public void RemoveScene(SceneNode node)
        {
            gtw.SelectAPI(String.Format("scenes.php?type=Remove&id={0}", node.ID));
        }
        /// <summary>
        /// Добавляен новый сценарий
        /// </summary>
        /// <param name="node">Сцена</param>
        /// <returns></returns>
        public SceneNode AddScene()
        {
            gtw.SelectAPI("scenes.php?type=Add");
            return GetScenes().Last();
        }
    }   
}
