#pragma once
#include <QString>
#include <QFont>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <QMap>
#include <QPoint>
#include <QPainterPath>

/// A struct containing the information for a GVGraph's node
struct GVNode
{
	/// The unique identifier of the node in the graph
	QString name;

	/// The position of the center point of the node from the top-left corner
	QPoint centerPos;

	/// The size of the node in pixels
	double height, width;
};

/// A struct containing the information for a GVGraph's edge
struct GVEdge
{
	/// The source and target nodes of the edge
	QString source;
	QString target;

	/// Path of the edge's line
	QPainterPath path;
};

/// An object containing a libgraph graph and its associated nodes and edges
class GVGraph
{
public:
	/// Default DPI value used by dot (which uses points instead of pixels for coordinates)
	static const qreal DotDefaultDPI;

	/*!
	 * \brief Construct a Graphviz graph object
	 * \param name The name of the graph, must be unique in the application
	 * \param font The font to use for the graph
	 * \param node_size The size in pixels of each node
	 */
	GVGraph(QString name, QFont font = QFont(), qreal node_size = 50);
	~GVGraph();

	/// Add and remove nodes
	void addNode(const QString& name);
	void addNodes(const QStringList& names);
	void removeNode(const QString& name);
	void clearNodes();

	/// Add and remove edges
	void addEdge(const QString& source, const QString& target, const std::string name);
	void removeEdge(const QString& source, const QString& target);
	void removeEdge(const QPair<QString, QString>& key);

	/// Set the font to use in all the labels
	void setFont(QFont font);
	void setRootNode(const QString& name);

	void applyLayout();

	void print();
	QList<GVNode> nodes() ;
	QList<GVEdge> edges() ;
private:
	GVC_t *_context;
	Agraph_t *_graph;
	QFont _font;
	QMap<QString, Agnode_t*> _nodes;
	QMap<QPair<QString, QString>, Agedge_t*> _edges;


	///// The agopen method for opening a graph
	//

	  Agraph_t* _agopen(QString name, Agdesc_s kind)
	{
		return agopen(const_cast<char *>(qPrintable(name)), kind, 0);
	}

	/// Add an alternative value parameter to the method for getting an object's attribute
	  QString _agget(void *object, QString attr, QString alt = QString())
	{
		QString str = agget(object, const_cast<char *>(qPrintable(attr)));

		if (str == QString())
			return alt;
		else
			return str;
	}

	/// Directly use agsafeset which always works, contrarily to agset
	  int _agset(void *object, QString attr, QString value)
	{
		return agsafeset(object, const_cast<char *>(qPrintable(attr)),
			const_cast<char *>(qPrintable(value)),
			const_cast<char *>(qPrintable(value)));
	}


	///// Set attrubutes for node
	  int _agnodeattr(Agraph_t *object, QString attr, QString value)
	{
		return agsafeset((void*)object, const_cast<char *>(qPrintable(attr)),
			const_cast<char *>(qPrintable(value)),
			const_cast<char *>(qPrintable(value)));
	}

	/// Set attrubutes for edges
	  int _agedgeattr(Agnode_t *object, QString attr, QString value)
	{
		return agsafeset((void*)object, const_cast<char *>(qPrintable(attr)),
			const_cast<char *>(qPrintable(value)),
			const_cast<char *>(qPrintable(value)));
	}

	  Agnode_t* _agnode(Agraph_t *object, QString value)
	{
		return agnode(object, const_cast<char *>(qPrintable(value)), true);
	}
	  int _gvLayout(GVC_t *gvc, graph_t *g, QString engine)
	{
		return gvLayout(gvc, g, const_cast<char *>(qPrintable(engine)));
	}
};

