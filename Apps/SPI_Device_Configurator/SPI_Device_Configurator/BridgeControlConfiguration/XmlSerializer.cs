using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Xml.Serialization;
using System.Xml;

namespace SPI_Device_Configurator.XMLSerializer
{
    //generic serialization,deserialization class
    public class GenericXMLSerializer
    {
        public string Serialize<T>(T obj)
        {
            string result = string.Empty;
            StringWriter writer = new StringWriter();
            XmlSerializer serializer = new XmlSerializer(typeof(T));

            serializer.Serialize(writer, obj);
            result = writer.ToString();

            return result;
        }

        public T Deserialize<T>(string xml)
        {
            T result = default(T);

            if (!string.IsNullOrEmpty(xml))
            {
                TextReader tr = new System.IO.StringReader(xml);
                XmlReader reader = XmlReader.Create(tr);
                XmlSerializer serializer = new XmlSerializer(typeof(T));

                if (serializer.CanDeserialize(reader))
                {
                    result = (T)serializer.Deserialize(reader);
                }
            }

            return result;
        }
    }

}
